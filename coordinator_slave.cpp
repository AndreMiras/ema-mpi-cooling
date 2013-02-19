#include "coordinator_slave.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
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

/**
 * sends SIMULATION_PHASE_ENDED message to master and calculators
 */
void send_simulation_phase_ended_message()
{
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    int message = SIMULATION_PHASE_ENDED;

    cout << "send_simulation_phase_ended_message: SIMULATION_PHASE_ENDED: " << SIMULATION_PHASE_ENDED << endl;

    // sends to master
    MPI_Send(&message, 1, MPI_INT, 0, 0, parent);

    // sends to calculators
    // send_message_to_calculators(&message, 1, MPI_INT); // TODO: test and put back in
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


vector<float> receive_all_new_temperatures()
{
    vector<float> temperatures_array;

    // TODO: receive temperatures MPI_Recv

    return temperatures_array;
}

float compute_mean_temperature(vector<float> temperatures_array)
{
    float mean_temperature;
    int temperatures_array_size = temperatures_array.size();

    for(int i=0; i < temperatures_array_size; i++)
    {
        mean_temperature += temperatures_array.at(i);
    }
    mean_temperature = mean_temperature / temperatures_array_size;

    return mean_temperature;
}


// TODO: perhaps we could use MPI_Bcast
void send_message_to_calculators(void* buffer, int count, MPI_Datatype datatype)
{
    int calculators_count = 9; // TODO: hardcoded
    for(int id=calculator_slave_id; id<calculators_count; id++)
    {
		// MPI_Send(&step_number, 1, MPI_INT, id, 0, MPI_COMM_WORLD);
		MPI_Send(buffer, count, datatype, id, 0, MPI_COMM_WORLD);
    }
}

/*
 * Le processus coordinateur fonctionne de la manière suivante
 * envoie le numéro du pas à tous les calculateurs
 * attends de recevoir toutes les nouvelles températures
 * calcule l’écart “Delta Tmoy”
 * “Delta Tmoy” = “Tmoy_courant” - “Tmoy_new”
 * si “Delta Tmoy” >= Epsilon on recommence, sinon on envoie un message de fin aux calculateurs
 */
void start_simulation(int simulation_step) // TODO: give relevant name
{
    // recv_from_all_calc(); // TODO

    // sends simulation step to calculators
    send_message_to_calculators(&simulation_step, 1, MPI_INT);

    // receive all calculators temperature and computes the mean temperature
    vector<float> temperatures_array = receive_all_new_temperatures();
    float mean_temperature = compute_mean_temperature(temperatures_array);

    float current_temperature = 20.0; // TODO: hardcoded
    float delta_temperature = abs(mean_temperature - current_temperature);
    if (delta_temperature > epsilon)
    {
        simulation_step++; // TODO: before or after
        // start_simulation(simulation_step); // TODO: commented out for debugging purpose
    }
}

int main(int argc, char *argv[])
{
	string prog_name(argv[0]);
	int myrank;
	int message;
	MPI_Comm parent;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_get_parent(&parent);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	mpi_debug(prog_name, myrank, parent, "Coordinator created");
	if (parent != MPI_COMM_NULL)
	{
		// the master sends the coordinator the init phase ended so the coordinator can start its work
        wait_init_phase_ended_message();

        // recv_from_all_calc(); // TODO

        // "toc" de simulation
        // start_simulation(0); // TODO: test and put back in

        send_simulation_phase_ended_message();
	}

	MPI_Finalize();
	return 0;
}
