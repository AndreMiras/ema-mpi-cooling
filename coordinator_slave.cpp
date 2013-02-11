#include "utils.h"
#include <vector>
#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main( int argc, char *argv[] )
{
	string prog_name(argv[0]);
	int myrank;
	MPI_Comm parent;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	cout << "Coordinator created and running" << endl;
	if (parent == MPI_COMM_NULL)
	{
		printf("Child %d : %s : No parent!\n", myrank, prog_name.c_str());
	}
	else {
		// MPI_Recv(&compteur, 1, MPI_INT, 0, 0, parent, &status);
		// TODO: check we can get the actual received size from the status
		// MPI_Recv(neighbours_array, neighbours_array_size, MPI_INT, 0, 0, parent, &status);

		const int src = 0;
		const int tag = 0;

		calculator_init recv;


		MPI_Datatype mpi_calculator_init_type;
		create_mpi_calculator_init_type(mpi_calculator_init_type);
		// MPI_Recv(&recv, 1, mpi_calculator_init_type, src, tag, parent, &status);

		printf("Child %d : %s : Receiving from parent!\n", myrank, prog_name.c_str());
		cout << endl;

		// MPI_Send(&compteur, 1, MPI_INT, 0, 0, parent);
		// printf("Child %d : %s : Sending to parent!\n", myrank, prog_name.c_str());
	}

	MPI_Finalize();
	return 0;
}
