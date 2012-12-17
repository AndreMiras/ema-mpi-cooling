#include <mpi.h>

#define NB_NEIGHBOURS 8
/*
 * Contains calculator neighbour and initial temperature
 */
typedef struct calculator_init_s {
	int neighbours_array[NB_NEIGHBOURS];
	float initial_temperature;
} calculator_init;


void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type);
