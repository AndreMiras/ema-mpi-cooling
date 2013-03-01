#ifndef COORDINATOR_SLAVE_H_
#define COORDINATOR_SLAVE_H_
#include "utils.h"
#include <mpi.h>
#include <vector>
#include <iostream>

using namespace std;

string prog_name;
int myrank;
MPI_Comm parent;
vector<vector<float> > temperature_matrix;

/**
 * Used to make the delta between previous mean temperature and mean temperature.
 * Initialised to current_temperature.
 */
float previous_mean_temperature = current_temperature;

const float epsilon = 0.1;

/**
 * Sends message to all calculators helper function
 */
void send_message_to_calculators(void* buffer, int count, MPI_Datatype datatype);

/**
 * Receives all new temperatures from calculators
 */
vector<float> receive_all_new_temperatures();

/**
 * Sends SIMULATION_PHASE_ENDED message to master and calculators
 */
void send_simulation_phase_ended_message();

/**
 * Wait for end of init phase message
 */
void wait_init_phase_ended_message();

/**
 * Inits empty temperature matrix with correct dimensions
 */
void init_temperature_matrix();

/*
 * Le processus coordinateur fonctionne de la manière suivante
 * envoie le numéro du pas à tous les calculateurs
 * attends de recevoir toutes les nouvelles températures
 * calcule l’écart “Delta Tmoy”
 * “Delta Tmoy” = “Tmoy_courant” - “Tmoy_new”
 * si “Delta Tmoy” >= Epsilon on recommence, sinon on envoie un message de fin aux calculateurs
 */
void start_simulation(int simulation_step);
#endif /* COORDINATOR_SLAVE_H_ */
