#include "utils.h"
#include <vector>
#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;


void wait_init_phase_ended_message()
{
    int message;
    MPI_Status status;
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);

    MPI_Recv(&message, 1, MPI_INT, 0, 0, parent, &status);
    if (message == INIT_PHASE_ENDED)
    {
        cout << "wait_init_phase_ended_message: INIT_PHASE_ENDED" << endl;
    }
    else
    {
        cout << "wait_init_phase_ended_message: Unexpected message: " << message << endl;
    }
}

void send_simulation_phase_ended_message()
{
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);

    int message = SIMULATION_PHASE_ENDED;
    cout << "send_simulation_phase_ended_message: SIMULATION_PHASE_ENDED: " << SIMULATION_PHASE_ENDED << endl;
    MPI_Send(&message, 1, MPI_INT, 0, 0, parent);
}

int main( int argc, char *argv[] )
{
	string prog_name(argv[0]);
	int myrank;
	int message;
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
		/*
		MPI_Recv(&message, 1, MPI_INT, 0, 0, parent, &status);
		printf("Child %d : %s : Receiving from parent!\n", myrank, prog_name.c_str());
		cout << endl;
		cout << "message: " << message << endl;
		if (message == INIT_PHASE_ENDED)
		{
			cout << "message is type of INIT_PHASE_ENDED!" << endl;
		}
		*/
		/*
		const int src = 0;
		const int tag = 0;

		calculator_init recv;


		MPI_Datatype mpi_calculator_init_type;
		create_mpi_calculator_init_type(mpi_calculator_init_type);
		// MPI_Recv(&recv, 1, mpi_calculator_init_type, src, tag, parent, &status);


		// MPI_Send(&compteur, 1, MPI_INT, 0, 0, parent);
		// printf("Child %d : %s : Sending to parent!\n", myrank, prog_name.c_str());
		*/
		// TODO: should actually be the other way around
		// the master sends the coordinator the init phase ended so the coordinator can start its work
        wait_init_phase_ended_message();

        // TODO: simulation code here

        send_simulation_phase_ended_message();
	}

	MPI_Finalize();
	return 0;
}
