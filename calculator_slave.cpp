#include "calculator_slave.h"
#include <vector>
#include <mpi.h>
#include <stdio.h>

enum {
	NORTH_INDEX,
	NORTH_EAST_INDEX,
	EAST_INDEX,
	SOUTH_EAST_INDEX,
	SOUTH_INDEX,
	SOUTH_WEST_INDEX,
	WEST_INDEX,
	NORTH_WEST_INDEX,
};

/*
 * Recreates a neighbours matrix from a given flat neighbours_array
 * 1 2 5 8 7 6 3 0
 * 0       1       2
 * 3       4       5
 * 6       7       8
 */
void create_matrix_from_neighbours_array(const int neighbours_array[], const int array_size, const int myrank, vector<vector<int> >& matrix)
{
	vector<int> array_vector;
	array_vector.push_back(neighbours_array[NORTH_WEST_INDEX]);
	array_vector.push_back(neighbours_array[NORTH_INDEX]);
	array_vector.push_back(neighbours_array[NORTH_EAST_INDEX]);
	matrix.push_back(array_vector);

	array_vector.clear();
	array_vector.push_back(neighbours_array[WEST_INDEX]);
	array_vector.push_back(myrank);
	array_vector.push_back(neighbours_array[EAST_INDEX]);
	matrix.push_back(array_vector);

	array_vector.clear();
	array_vector.push_back(neighbours_array[SOUTH_WEST_INDEX]);
	array_vector.push_back(neighbours_array[SOUTH_INDEX]);
	array_vector.push_back(neighbours_array[SOUTH_EAST_INDEX]);
	matrix.push_back(array_vector);
}

/**
 * Receveives the initial structure (step 2), containing:
 *  - neighbours_array
 *  - initial_temperature
 */
void receive_init_struct()
{
    const int src = 0;
    const int tag = 0;
	int myrank;
	MPI_Comm parent;
	MPI_Status status;
	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    calculator_init recv;
    MPI_Datatype mpi_calculator_init_type;

    create_mpi_calculator_init_type(mpi_calculator_init_type);
    // MPI_Recv(neighbours_array, neighbours_array_size, MPI_INT, 0, 0, parent, &status);
    MPI_Recv(&recv, 1, mpi_calculator_init_type, src, tag, parent, &status);
    my_temperature = recv.initial_temperature;
    printf("Rank %d: Received: my_temperature = %f\n", myrank, my_temperature);

    printf("Child %d : %s : Receiving from parent!\n", myrank, prog_name.c_str());
    /*
    cout << "neighbours_array[" << NB_NEIGHBOURS << "] = ";
    display_array(recv.neighbours_array, NB_NEIGHBOURS);
    */
    vector<vector<int> > matrix;
    create_matrix_from_neighbours_array(recv.neighbours_array, NB_NEIGHBOURS, myrank, matrix);
    /*
    cout << "neighbours_matrix[" << matrix.size() << "][" << matrix[0].size() << "] = ";
    display_matrix<int>(matrix);
    */
    cout << endl;
}

// Envoi temperature aux voisins
void send_temperature_to_neighbours()
{
    send_message_to_neighbours<float>(my_temperature, 1, MPI_FLOAT);
}

// Recevoir temperature des voisins
vector<float> receive_temperatures_from_neighbours()
{
    vector<float> temperatures;

    temperatures = receive_message_from_neighbours<float>(1, MPI_FLOAT);

    return temperatures;
}

// Calculer la nouvelle temperature
float compute_new_temperature_mean(const vector<float>& temperatures)
{
    float temperature = my_temperature;

    for(int i=0; i < temperatures.size(); i++)
    {
        temperature += temperatures.at(0);
    }
    temperature = (temperature / (temperatures.size() + 1));
    
    return temperature;
}

// Envoi nouvelle temperature au coordinateur
void send_new_temperature_to_coordinator(float new_temperature)
{
   // TODO
}


/**
 * Sends temperature to neighbours asynchroniously.
 * Receives neighbours' temperatures.
 */
void temperatures_exchange()
{
    // Envoi temperature aux voisins
    send_temperature_to_neighbours();

    // Recevoir temperature des voisins
    vector<float> temperatures = receive_temperatures_from_neighbours();

    // Calculer la nouvelle temperature
    float new_temperature;
    new_temperature = compute_new_temperature_mean(temperatures);

    // Envoi nouvelle temperature au coordinateur
    send_new_temperature_to_coordinator(new_temperature);
}

// Fonction Reception d'un int
int receive_simulation_step()
{
    MPI_Status status;
    int simulation_step;

    MPI_Recv(&simulation_step, 1, MPI_INT,  coordinator_slave_id, 0, MPI_COMM_WORLD, &status);

    return simulation_step;
}

// TODO: review this code (written by Del)
/**
 * This is step 4
 */
void wait_for_int_from_coordinator()
{
    int myrank; //Numéro de processus
    MPI_Comm parent;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    int simulation_step = receive_simulation_step();

    // mpi_debug(prog_name, myrank, parent, "wait_for_int_from_coordinator begin");
    simulation_step = SIMULATION_PHASE_ENDED; // TODO: for debugging

    if(simulation_step > 0)
    {   
        // TODO: put back in temperatures_exchange();
        // TODO: back to wait_for_int_from_coordinator()
    }
    else
    {
        if(simulation_step == SIMULATION_PHASE_ENDED)
        {
            if (parent == MPI_COMM_NULL)
            {
                printf("Coordinator %d : Coord : Pas de maitre !\n", myrank);
            }
            else
            {
                int compteur = 0;
                // cout << "Fin du traitement du calculator " << myrank << endl;
                
                // TODO: review and finish up
                //MPI_Send(&compteur, 1, MPI_INT, 0, 0,parent );
                // cout << "Envoi 0 du calculator " << myrank <<endl;
            }
        }
    }
}


int main(int argc, char *argv[])
{
	int myrank;
	MPI_Comm parent;
	MPI_Status status;

	prog_name = argv[0];
	MPI_Init(&argc, &argv);

	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    mpi_debug(prog_name, myrank, parent, "Calculator created");
	if (parent != MPI_COMM_NULL)
	{
		// MPI_Recv(&compteur, 1, MPI_INT, 0, 0, parent, &status);
		// TODO: check we can get the actual received size from the status
		// MPI_Recv(neighbours_array, neighbours_array_size, MPI_INT, 0, 0, parent, &status);

        receive_init_struct();

		// MPI_Send(&compteur, 1, MPI_INT, 0, 0, parent);
		// printf("Child %d : %s : Sending to parent!\n", myrank, prog_name.c_str());
        wait_for_int_from_coordinator();
        mpi_debug(prog_name, myrank, parent, "Message de fin");
	}
        

	MPI_Finalize();
	return 0;
}
