#include "utils.h"

/*
 * Creates a type for struct calculator_init
 */
void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type)
{
	const int nitems = 2;   // neighbours_array and initial_temperature
	int blocklengths[nitems] = {
		NB_NEIGHBOURS,      // each case has 8 neighbours
		1
	};
	MPI_Datatype types[nitems] = {MPI_INT, MPI_FLOAT};
	// MPI_Datatype mpi_calculator_init_type;
	MPI_Aint offsets[nitems];

	offsets[0] = offsetof(calculator_init, neighbours_array);
	offsets[1] = offsetof(calculator_init, initial_temperature);

	MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_calculator_init_type);
	MPI_Type_commit(&mpi_calculator_init_type);
}
