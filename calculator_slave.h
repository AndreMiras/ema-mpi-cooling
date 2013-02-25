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
int receive_simulation_step();
void send_new_temperature_to_coordinator(float new_temperature);
float compute_new_temperature_mean(const vector<float>& temperatures);
void temperatures_exchange();
void wait_for_int_from_coordinator();
double process_new_temperatures(const vector<float>& temperatures);
vector<float> receive_temperatures_from_neighbours();
void send_temperature_to_neighbours();
void receive_init_struct();
void create_matrix_from_neighbours_array(const int neighbours_array[], const int array_size, const int myrank, vector<vector<int> >& matrix);


// TODO: use generics rather than void
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
    const int tag = 0; // TODO[DRY]: use global utils.h tag value
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
            string message = "receive_message_from_neighbours MPI_Recv, neighbour_id: " + t_to_string(neighbour_id) + " begin";
            mpi_debug(prog_name, myrank, parent, message);
            MPI_Recv(&buffer, count, datatype, neighbour_id, tag, MPI_COMM_WORLD, &status); // TODO: debug put back in
            mpi_debug(prog_name, myrank, parent, "receive_message_from_neighbours MPI_Recv end");
        }
        buffers.push_back(buffer); // TODO: finish up usig generics
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
    T tempBuffer = buffer; // because MPI_Send only acccepts "void" and not "const void"
    MPI_Request request;
    float temperature_for_tests = 30.0;

    for(int i=0; i<NB_NEIGHBOURS; i++)
    {
        id = neighbours_array[i];
        if (id != NO_NEIGHBOUR_VALUE)
        {
            string message = "send_asynchronous_message_to_neighbours: MPI_Isend to id=" + t_to_string(id);
            mpi_debug(prog_name, myrank, parent, message);
            MPI_Isend(&tempBuffer, count, datatype, id, 0, MPI_COMM_WORLD, &request);
            mpi_debug(prog_name, myrank, parent, "send_asynchronous_message_to_neighbours end");
        }
    }
}


#endif /* CALCULATOR_SLAVE_H_ */
