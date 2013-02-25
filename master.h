#ifndef MASTER_H_
#define MASTER_H_
#include <mpi.h>
#include <vector>
#include <iostream>

using namespace std;

const int tag = 0;
string prog_name;
int myrank;
MPI_Comm parent;

vector<vector<float> > temperature_matrix;


float get_initial_temperature(int process);

/**
 * returns the temperature of a given process
 */
float get_temperature(int process);
#endif /* MASTER_H_ */
