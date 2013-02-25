#ifndef COORDINATOR_SLAVE_H_
#define COORDINATOR_SLAVE_H_
#include <iostream>
#include <mpi.h>

using namespace std;

string prog_name;
int myrank;
MPI_Comm parent;

const float epsilon = 0.5;

void send_message_to_calculators(void* buffer, int count, MPI_Datatype datatype);
#endif /* COORDINATOR_SLAVE_H_ */
