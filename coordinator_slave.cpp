#ifndef CALCULATOR_SLAVE_H_
#define CALCULATOR_SLAVE_H_
#include "coordinator_slave.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


void wait_init_phase_ended_message()
{
    int message;
    MPI_Status status;

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
    int message = SIMULATION_PHASE_ENDED;

    cout << "send_simulation_phase_ended_message: SIMULATION_PHASE_ENDED: " << SIMULATION_PHASE_ENDED << endl;

    // sends to master
    MPI_Send(&message, 1, MPI_INT, 0, 0, parent);

    // sends to calculators
    send_message_to_calculators(&message, 1, MPI_INT);
}


// TODO: deprecated?
int recv_from_calc(int id){
    int message = 0;
    MPI_Status status;

    //TODO Reception
    //MPI_Recv(&message, 1, MPI_INT, id, 0, 1, &status);
    
    message++;
    
    return message;
}

// TODO: deprecated?
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
    string message;
	float temperature;
    int row, col;
	MPI_Status status;
    vector<float> temperatures_array;

    mpi_debug(prog_name, myrank, parent, "receive_all_new_temperatures");
    // TODO: perhaps we could use MPI_Gather
    for(int calculator_id = calculator_slave_first_id; calculator_id <= calculator_slave_last_id; calculator_id++)
    {
        message = "receive_all_new_temperatures: Receiving one temperature from: " + t_to_string(calculator_id);
        mpi_debug(prog_name, myrank, parent, message);
        mpi_debug(prog_name, myrank, parent, "MPI_Recv begin");
        MPI_Recv(&temperature, 1, MPI_FLOAT, calculator_id, 0, MPI_COMM_WORLD, &status);
        message = "MPI_Recv end, Received one temperature from: " + t_to_string(calculator_id) + " end";
        mpi_debug(prog_name, myrank, parent, message);
        temperatures_array.push_back(temperature);

        // updates the temperature_matrix
        get_calculator_row_col(calculator_id, matrix_row_size, matrix_col_size, row, col);
        temperature_matrix[row][col] = temperature;


    }
    mpi_debug(prog_name, myrank, parent, "receive_all_new_temperatures end");
    // display_array(temperatures_array);
    display_matrix(temperature_matrix);

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
void send_message_to_calculators(void* buffer, const int count, const MPI_Datatype datatype)
{
    mpi_debug(prog_name, myrank, parent, "send_message_to_calculators");

    for(int id = calculator_slave_first_id; id <= calculator_slave_last_id; id++)
    {
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
    string message = "start_simulation simulation_step: " + t_to_string(simulation_step);
    mpi_debug(prog_name, myrank, parent, message);
    // sends simulation step to calculators
    send_message_to_calculators(&simulation_step, 1, MPI_INT);

    // receive all calculators temperature and computes the mean temperature
    vector<float> temperatures_array = receive_all_new_temperatures();
    float mean_temperature = compute_mean_temperature(temperatures_array);

    float delta_temperature = abs(mean_temperature - current_temperature);
    if (delta_temperature > epsilon)
    {
        simulation_step++;
        start_simulation(simulation_step);
    }
    else
    {
        mpi_debug(prog_name, myrank, parent, "delta_temperature > epsilon");
    }
}

void init_temperature_matrix()
{
    temperature_matrix.clear();
    vector<float> one_row(matrix_col_size);
    for(int i = 0; i < matrix_row_size; i++)
    {
        temperature_matrix.push_back(one_row);
    }
}

int main(int argc, char *argv[])
{
    prog_name = argv[0];
    int message;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_get_parent(&parent);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    mpi_debug(prog_name, myrank, parent, "Coordinator created");
    if (parent != MPI_COMM_NULL)
    {
        // the master sends the coordinator the init phase ended so the coordinator can start its work
        wait_init_phase_ended_message();
    init_temperature_matrix();

        // recv_from_all_calc(); // TODO

        // "toc" de simulation
        start_simulation(1);
        send_simulation_phase_ended_message();
    }

    mpi_debug(prog_name, myrank, parent, "MPI_Finalizing");
    MPI_Finalize();
    mpi_debug(prog_name, myrank, parent, "MPI_Finalized");
    return 0;
}
#endif /* CALCULATOR_SLAVE_H_ */
