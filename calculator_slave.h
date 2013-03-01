#ifndef CALCULATOR_SLAVE_H_
#define CALCULATOR_SLAVE_H_
#include "utils.h"
#include <iostream>
using namespace std;

string prog_name;
int myrank;
MPI_Comm parent;

int neighbours_array[NB_NEIGHBOURS]; // neighbours array to be received
float my_temperature; // calculator temperature

int main(int argc, char *argv[]);

/**
 * This is step 4 that starts the simulation
 */
void start_simulation();

/**
 * Waits for a new simulation step int
 */
int receive_simulation_step();

/**
 * Sends a given temperature to coordinator
 */
void send_new_temperature_to_coordinator(float new_temperature);

/**
 * Sends temperature to neighbours asynchroniously.
 * Receives neighbours' temperatures.
 */
void temperatures_exchange();
void wait_for_int_from_coordinator();
double process_new_temperatures(const vector<float>& temperatures);

/**
 * Receives temperature from neighbours
 */
vector<float> receive_temperatures_from_neighbours();

/**
 * Sends temperature to neighbours asynchroniously
 */
void send_temperature_to_neighbours();

/**
 * Receveives the initial structure (step 2), containing:
 *  - neighbours_array
 *  - initial_temperature
 */
void receive_init_struct();

/*
 * Recreates a neighbours matrix from a given flat neighbours_array
 * the given array:
 * int neighbours_array[] = { 1, 2, 5, 8, 7, 6, 3, 0 }
 * would return the following matrix:
 * {
 *  {0, 1, 2},
 *  {3, x, 5},
 *  {6, 7, 8}
 * }
 */
void create_matrix_from_neighbours_array(const int neighbours_array[], const int array_size, const int myrank, vector<vector<int> >& matrix);


/**
 * count represents the size of one buffers[] void element
 * i.e. sizeof(buffers[0]) == count
 */
template <class T>
vector<T> receive_message_from_neighbours(const int count, const MPI_Datatype datatype)
{
    vector<T> buffers;
    T buffer;
    MPI_Status status;
    int neighbour_id;

    for(int i=0; i<NB_NEIGHBOURS; i++)
    {
        neighbour_id = neighbours_array[i];
        if (neighbour_id == NO_NEIGHBOUR_VALUE)
        {
            buffer = current_temperature;
        }
        else
        {
            MPI_Recv(&buffer, count, datatype, neighbour_id, tag, MPI_COMM_WORLD, &status);
        }
        buffers.push_back(buffer);
    }

    return buffers;
}


template <class T>
void send_message_to_neighbours(const T& buffer, const int count, const MPI_Datatype datatype)
{
    int id;
    T tempBuffer = buffer; // because MPI_Send only acccepts "void" and not "const void"

    for(int i=0; i<NB_NEIGHBOURS; i++)
    {
        id = neighbours_array[i];
        MPI_Send(&tempBuffer, count, datatype, id, 0, MPI_COMM_WORLD);
    }
}


template <class T>
void send_asynchronous_message_to_neighbours(const T& buffer, const int count, const MPI_Datatype datatype)
{
    int id;
    T tempBuffer = buffer; // MPI_Send only acccepts "void" but not "const void"
    MPI_Request request;

    for(int i=0; i<NB_NEIGHBOURS; i++)
    {
        id = neighbours_array[i];
        if (id != NO_NEIGHBOUR_VALUE)
        {
            MPI_Isend(&tempBuffer, count, datatype, id, 0, MPI_COMM_WORLD, &request);
        }
    }
}


#endif /* CALCULATOR_SLAVE_H_ */
