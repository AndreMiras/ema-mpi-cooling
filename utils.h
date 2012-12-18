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


void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type);
void display_matrix(const vector<vector<int> > matrix);
void display_array(const int array[], const int array_size);
