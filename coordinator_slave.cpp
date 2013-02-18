#include "coordinator_slave.h"
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



int recv_from_calc(int id){
    int message = 0;
    MPI_Status status;
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);

    //TODO Reception
    //MPI_Recv(&message, 1, MPI_INT, id, 0, 1, &status);
    
    message++;
    
    return message;
}

void recv_from_all_calc() {
       int tab[9];
       for(int i=1; i< 9; i++)
       {
             tab[i-1] = recv_from_calc(i);
             cout<<"Coordinator Tab["<<(i-1)<<"] = "<<tab[i-1]<<endl;
       }
}


void receive_all_new_temperatures()
{
}

void send_step_number_to_all_calculators()
{
    cout << "send_step_number_to_all_calculators" << endl;
    int step_number = 0; // TODO: hardcoded
    const int calculators_count = 9; // FIXME: hardcoded

    for(int id=calculator_slave_id; id<calculators_count; id++)
    {
		MPI_Send(&step_number, 1, MPI_INT, id, 0, MPI_COMM_WORLD);
    }
}

void send_end_message_to_calculators()
{
}

float compute_delta_temperature()
{
    float delta = 0.0;

    return delta;
}

/*
 * Le processus coordinateur fonctionne de la manière suivante
 * envoie le numéro du pas à tous les calculateurs
 * attends de recevoir toutes les nouvelles températures
 * calcule l’écart “Delta Tmoy”
 * “Delta Tmoy” = “Tmoy_courant” - “Tmoy_new”
 * si “Delta Tmoy” >= Epsilon on recommence, sinon on envoie un message de fin aux calculateurs
 */
void step4() // TODO: give relevant name
{
    send_step_number_to_all_calculators();
    receive_all_new_temperatures();
    float delta_temperature = compute_delta_temperature();
    epsilon = 0.0; // TODO: overridded for debugging purpose
    if (delta_temperature > epsilon)
    {
        // step4(); // TODO: commented out for debugging purpose
    }
    send_end_message_to_calculators();
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
		// TODO: should actually be the other way around
		// the master sends the coordinator the init phase ended so the coordinator can start its work
        wait_init_phase_ended_message();

        recv_from_all_calc();

        // TODO: simulation code here

        send_simulation_phase_ended_message();
	}

	MPI_Finalize();
	return 0;
}
