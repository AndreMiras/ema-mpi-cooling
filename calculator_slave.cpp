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

void receive_init_struct()
{
    const int src = 0;
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

void send_temperature_to_neighbours()
{
    send_asynchronous_message_to_neighbours<float>(my_temperature, 1, MPI_FLOAT);
}

vector<float> receive_temperatures_from_neighbours()
{
    vector<float> temperatures;

    temperatures = receive_message_from_neighbours<float>(1, MPI_FLOAT);

    return temperatures;
}

void send_new_temperature_to_coordinator(float new_temperature)
{
    MPI_Send(&new_temperature, 1, MPI_FLOAT, coordinator_slave_id, 0, MPI_COMM_WORLD);
}


void temperatures_exchange()
{
    // Sends temperature to neigbours
    send_temperature_to_neighbours();

    // Receives neighbours temperature
    vector<float> temperatures = receive_temperatures_from_neighbours();

    // Computes the new mean
    temperatures.push_back(my_temperature);
    my_temperature = compute_mean(temperatures);

    // Sends new temperature to coordinator
    send_new_temperature_to_coordinator(my_temperature);
}

int receive_simulation_step()
{
    MPI_Status status;
    int simulation_step;

    MPI_Recv(&simulation_step, 1, MPI_INT,  coordinator_slave_id, 0, MPI_COMM_WORLD, &status);

    return simulation_step;
}

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
