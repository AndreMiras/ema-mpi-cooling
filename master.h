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

int get_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
    int north_or_south = 0,
    int east_or_west = 0);

/**
 * Returns north neighbour id of a given row/col process.
 */
int get_north_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_north_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_south_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_south_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_south_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
 */
int get_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col);

/*
 * Same as get_north_neighbour_from_matrix.
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

/**
 * Initialises temperature matrix.
 */
void init_initial_temperature_matrix(vector<vector<float> >& matrix, const int matrix_row_size, const int matrix_col_size);

/**
 * Helper function that returns initial temperature for a given process.
 * We're currently giving a known (hardcoded) temperature for testing purposes,
 * but that could easily be a random temperature.
 */
float get_initial_temperature(int process);

/**
 * Sends init phase ended message t coordinator.
 */
void send_init_phase_ended_message(const MPI_Comm& intercomm);

/**
 * Waits for end of simulation message from coordinator.
 */
void wait_simulation_phase_ended_message(const MPI_Comm& intercomm);

/**
 * Creates coordinator and slaves processes and returns the MPI_Comm used.
 */
MPI_Comm create_coordinator_slave_and_calculators_slaves();

/**
 * Creates the neighbours_array and send it to the calculators.
 */
void neighbour_array_creation_and_passing(const MPI_Comm& intercomm);

#endif /* MASTER_H_ */
