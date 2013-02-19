#include "utils.h"

/*
 * Creates a type for struct calculator_init
 * TODO[perfs]: the MPI_Datatype object should be created once and saved statically
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

void mpi_debug(const string& prog_name, const int& rank, const MPI_Comm& parent, const string& message)
{
    string parent_str;

    if (parent == MPI_COMM_NULL)
    {
        parent_str = "MPI_COMM_NULL";
        // cout << "prog_name:  " << prog_name.c_str() << ", rank: " << myrank << ", parent: MPI_COMM_NULL" << endl;
    }
    else {
        parent_str = t_to_string(parent);
    }
    cout << "prog_name:  " << prog_name.c_str() <<
            ", rank: " << rank <<
            ", parent: " << parent_str <<
            ", message: " << message << endl;
}
