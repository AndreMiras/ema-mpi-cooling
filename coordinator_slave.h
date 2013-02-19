#include <iostream>
#include <mpi.h>

using namespace std;

string prog_name;

const float epsilon = 0.5;

void send_message_to_calculators(void* buffer, int count, MPI_Datatype datatype);
