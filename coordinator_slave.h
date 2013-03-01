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

void send_message_to_calculators(void* buffer, int count, MPI_Datatype datatype);

/**
 * Init empty temperature matrix with correct dimensions
 */
void init_temperature_matrix();
#endif /* COORDINATOR_SLAVE_H_ */
