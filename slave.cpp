#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main( int argc, char *argv[] )
{
	string prog_name(argv[0]);
	int compteur, myrank;
	MPI_Comm parent;
	MPI_Status etat;

	MPI_Init (&argc, &argv);

	MPI_Comm_get_parent (&parent);
	MPI_Comm_rank (MPI_COMM_WORLD,&myrank);

	if (parent == MPI_COMM_NULL)
	{
		printf("Child %d : %s : No parent!\n", myrank, prog_name.c_str());
	}
	else {
		MPI_Recv(&compteur, 1, MPI_INT, 0, 0, parent, &etat);
		printf("Child %d : %s : Receiving from parent!\n", myrank, prog_name.c_str());
		MPI_Send(&compteur, 1, MPI_INT, 0, 0, parent);
		printf("Child %d : %s : Sending to parent!\n", myrank, prog_name.c_str());
	}

	MPI_Finalize();
	return 0;
}
