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

/*
 * Phase 3: un float correspondant à la temperature initiale du carré (fixée en dur, puis lue dans un fichier de config)
 * TODO: donner une temperature aléatoire
 */
float get_initial_temperature(int process);

int get_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
    int north_or_south = 0,
    int east_or_west = 0);

int get_north_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_north_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * same as get_north_neighbour_from_matrix
 */
int get_north_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Given a matrix and a row, col couple, returns the neighbours_array (clock wize)
 * The neighbours_array is given in this order: NORTH, NORTH-EAST, EAST, SOUTH-EAST, SOUTH, SOUTH-WEST, WEST, NORTH-WEST
 * matrix = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
 * };
 * row = 1, col = 1
 * => neighbours_array = {1, 2, 5, 8, 7, 6, 3, 0}
 */
void get_neighbours_array_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
	int neighbours_array[],
	int neighbours_array_size);


/*
 * Given a matrix and a row, col couple, returns the north neighbour
 * matrix = {
 *      {0, 1, 2},
 *      {3, 4, 5},
 *      {6, 7, 8},
 * };
 * row = 1, col = 1
 * => north_neighbour = 1
 */
int get_north_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

#endif /* MASTER_H_ */
