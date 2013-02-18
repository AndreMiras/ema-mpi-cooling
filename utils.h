#include <vector>
#include <mpi.h>

using namespace std;

#define NB_NEIGHBOURS 8
/*
 * Contains calculator neighbour and initial temperature
 */
typedef struct calculator_init_s {
	int neighbours_array[NB_NEIGHBOURS];
	float initial_temperature;
} calculator_init;

enum message_type {
	INIT_PHASE_ENDED = 0,
	SIMULATION_PHASE_ENDED,
};

void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type);

void display_matrix(const vector<vector<int> > matrix);

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
