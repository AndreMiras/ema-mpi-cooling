#ifndef MASTER_H_
#define MASTER_H_
#include <mpi.h>
#include <vector>
#include <iostream>

using namespace std;

string prog_name;
int myrank;
MPI_Comm parent;

vector<vector<float> > initial_temperature_matrix;

float get_initial_temperature(int process);

int get_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
    int north_or_south = 0,
    int east_or_west = 0);
#endif /* MASTER_H_ */
