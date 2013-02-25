#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <mpi.h>

using namespace std;

const int coordinator_slave_id = 0; // l'id du coordinateur
const int calculator_slave_id = 1; // les id esclaves demarrent a 1

// Matrix plate dimension
const int matrix_row_size = 3;
const int matrix_col_size = 4;

// number of coordinator process
const int coordinator_slave_count = 1;
// number of calculator processes
const int calculator_slave_count = matrix_row_size * matrix_col_size;
const int nb_instances = 2;

const float current_temperature = 20.0;

const int NO_NEIGHBOUR_VALUE = -1;

/*
 * Neighbours count.
 * It could be more or less than 8 neighbours,
 * for example if plates are not squared.
 */
#define NB_NEIGHBOURS 8
/*
 * Contains calculator neighbour and initial temperature
 */
typedef struct calculator_init_s {
	int neighbours_array[NB_NEIGHBOURS];
	float initial_temperature;
} calculator_init;

/*
enum message_type {
	INIT_PHASE_ENDED = 0,
	SIMULATION_PHASE_ENDED,
};
*/
const int SIMULATION_PHASE_ENDED = -1;
const int INIT_PHASE_ENDED = 0;

void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type);

// void display_matrix(const vector<vector<int> > matrix);

template <class T>
void display_array(const T array[], const int array_size)
{
	// cout << "array[" << array_size << "] = ";
	cout << "{ ";
	for(int i=0; i<array_size; i++)
	{
		// printf("array[%i]: %i\n", i, array[i]);
		cout << array[i];
		if (i != (array_size -1))
		{
			cout << ", ";
		}
	}
	cout << " }" << endl;
}

template <class T>
void display_array(const vector<T> array)
{
    display_array(array.data(), array.size());
}


template <typename T>
void display_matrix(const vector<vector<T> > matrix)
{
	cout << "{" << endl;
	for (int row=0; row < matrix.size(); row++)
	{
		cout << "  ";
		display_array<T>(matrix[row].data(), matrix[row].size());
	}
	cout << "}" << endl;
}
void mpi_debug(const string& prog_name, const int& rank, const MPI_Comm& parent, const string& message="No message");

template<class T>
std::string t_to_string(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}
#endif /* UTILS_H_ */
