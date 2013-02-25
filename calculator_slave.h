#ifndef CALCULATOR_SLAVE_H_
#define CALCULATOR_SLAVE_H_
#include "utils.h"
#include <iostream>
using namespace std;

string prog_name;
int neighbours_array[NB_NEIGHBOURS]; // neighbours array to be received
float temperature; // calculator temperature

int main(int argc, char *argv[]);
void send_message_to_neighbours(void* buffer, const int count, const MPI_Datatype datatype);
vector<void> receive_message_from_neighbours(const int count, const MPI_Datatype datatype);
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
    int id;

    for(int i=0; i<NB_NEIGHBOURS; i++)
    {
        id = neighbours_array[i];
        if (id == NO_NEIGHBOUR_VALUE)
        {
            buffer = current_temperature;
        }
        else
        {
            MPI_Recv(&buffer, count, datatype, id, tag, MPI_COMM_WORLD, &status);
        }
        buffers.push_back(buffer); // TODO: finish up usig generics
    }

    return buffers;
}



#endif /* CALCULATOR_SLAVE_H_ */
