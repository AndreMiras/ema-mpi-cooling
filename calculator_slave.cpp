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
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    calculator_init recv;
    MPI_Datatype mpi_calculator_init_type;

    create_mpi_calculator_init_type(mpi_calculator_init_type);
    MPI_Recv(&recv, 1, mpi_calculator_init_type, src, tag, parent, &status);
    my_temperature = recv.initial_temperature;

    /*
    cout << "neighbours_array[" << NB_NEIGHBOURS << "] = ";
    display_array(recv.neighbours_array, NB_NEIGHBOURS);
    */
    memcpy(neighbours_array, recv.neighbours_array, sizeof(int) * NB_NEIGHBOURS);
    vector<vector<int> > matrix;
    create_matrix_from_neighbours_array(neighbours_array, NB_NEIGHBOURS, myrank, matrix);
    /*
    cout << "neighbours_matrix[" << matrix.size() << "][" << matrix[0].size() << "] = ";
    display_matrix<int>(matrix);
    cout << endl;
    */
}

// Envoi temperature aux voisins
void send_temperature_to_neighbours()
{
    send_asynchronous_message_to_neighbours<float>(my_temperature, 1, MPI_FLOAT);
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
        temperature += temperatures.at(i);
    }
    temperature = (temperature / (temperatures.size() + 1));
    
    return temperature;
}

// Envoi nouvelle temperature au coordinateur
void send_new_temperature_to_coordinator(float new_temperature)
{
    MPI_Send(&new_temperature, 1, MPI_FLOAT, coordinator_slave_id, 0, MPI_COMM_WORLD);
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
    my_temperature = new_temperature;

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
void start_simulation()
{
    int simulation_step;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    do
    {   
        simulation_step = receive_simulation_step();
        temperatures_exchange();
    }
    while (simulation_step > 0);

    /*
    if (simulation_step == SIMULATION_PHASE_ENDED)
    {
        mpi_debug(prog_name, myrank, parent, "simulation_step == SIMULATION_PHASE_ENDED");
    }
    */
}


int main(int argc, char *argv[])
{
	MPI_Status status;

	prog_name = argv[0];
	MPI_Init(&argc, &argv);

	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (parent != MPI_COMM_NULL)
	{
        receive_init_struct();
        start_simulation();
	}

	MPI_Finalize();
	return 0;
}
