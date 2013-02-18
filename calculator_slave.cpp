#include "calculator_slave.h"
#include "utils.h"
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
    printf("Rank %d: Received: temperature = %f\n", myrank, recv.initial_temperature);

    printf("Child %d : %s : Receiving from parent!\n", myrank, prog_name.c_str());
    cout << "neighbours_array[" << NB_NEIGHBOURS << "] = ";
    display_array(recv.neighbours_array, NB_NEIGHBOURS);
    vector<vector<int> > matrix;
    create_matrix_from_neighbours_array(recv.neighbours_array, NB_NEIGHBOURS, myrank, matrix);
    cout << "neighbours_matrix[" << matrix.size() << "][" << matrix[0].size() << "] = ";
    display_matrix<int>(matrix);
    cout << endl;
}

// Envoi temperature aux voisins
void send_temperature_to_neighbours()
{
    
}

//Recevoir temperature des voisins
void recv_temperature_from_neighbours(int* temperatures)
{
    
}

//Calculer la nouvelle temperature
double process_new_temperature(int* temperatures)
{
    double temperature;
     
        //(si voisin = -1, alors TemperatureReçue[voisin] = 20°C (température ambiante de la plaque))
    
    //temperature = (Tcourant + somme(voisin =0 ? 7)(TemperatureReçue[voisin]) ) / 9
    
    return temperature;
}

//Envoi nouvelle temperature au coordinateur
void send_new_temperature(double new_temperature)
{
    
}



void traitement_temperatures()
{
    // Envoi temperature aux voisins
    send_temperature_to_neighbours();

    //Recevoir temperature des voisins
    int temperatures[9];
    recv_temperature_from_neighbours(temperatures);

    //Calculer la nouvelle temperature
    double new_temperature;
    new_temperature = process_new_temperature(temperatures);

    //Envoi nouvelle temperature au coordinateur
    send_new_temperature(new_temperature);
}

// TODO: review this code (written by Del)
/**
 * This is step 4
 */
void send_end_message()
{
    int myrank; //Numéro de processus
    MPI_Comm parent;
    MPI_Status etat;

    MPI_Comm_rank (MPI_COMM_WORLD,&myrank);

    int coordinateur;

    //TODO Fonction Reception d'un int
    //Sinon, en attente de reception
    //MPI_Recv(&coordinateur, 0, int, 0, 0, parent, &etat); // pas sure pour le "parent"

    if(coordinateur > 0)
    {   
        traitement_temperatures();   
        //TODO Back to wait_for_int_from_coord()
    }
    else
    {
        if(coordinateur == -1 )
        {
            if (parent == MPI_COMM_NULL)
            {
                printf ("Coordinator %d : Coord : Pas de maitre !\n", myrank);
            }
            else
            {
                int compteur = 0;
                cout<<"Fin du traitement du calculator "<<myrank<<endl;
                
                //REVIEWWWWWWWWWWWWWWWWWWWWWWWWWWW
                //MPI_Send(&compteur, 1, MPI_INT, 0, 0,parent );
                cout<<"Envoi 0 du calculator "<<myrank<<endl;
            }
        }
    }

}




int main(int argc, char *argv[])
{
	int neighbours_array[NB_NEIGHBOURS]; // neighbours array to be received
	int myrank;
	MPI_Comm parent;
	MPI_Status status;

	prog_name = argv[0];
	MPI_Init(&argc, &argv);

	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (parent == MPI_COMM_NULL)
	{
		printf("Child %d : %s : No parent!\n", myrank, prog_name.c_str());
	}
	else {
		// MPI_Recv(&compteur, 1, MPI_INT, 0, 0, parent, &status);
		// TODO: check we can get the actual received size from the status
		// MPI_Recv(neighbours_array, neighbours_array_size, MPI_INT, 0, 0, parent, &status);

                receive_init_struct();

		// MPI_Send(&compteur, 1, MPI_INT, 0, 0, parent);
		// printf("Child %d : %s : Sending to parent!\n", myrank, prog_name.c_str());
	}
        
        send_end_message();

	MPI_Finalize();
	return 0;
}




