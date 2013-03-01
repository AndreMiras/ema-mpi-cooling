#ifndef UTILS_H_
#define UTILS_H_
#include <mpi.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

static vector<vector<int> > calculators_ids_matrix; // TODO[deprecated]: should later be computed dynamically

static const int coordinator_slave_id = 0; // l'id du coordinateur
static const int calculator_slave_first_id = 1; // les id esclaves demarrent a 1

// Matrix plate dimension
static const int matrix_row_size = 3;
static const int matrix_col_size = 4;

// number of coordinator process
static const int coordinator_slave_count = 1;
// number of calculator processes
static const int calculator_slave_count = matrix_row_size * matrix_col_size;
static const int calculator_slave_last_id = calculator_slave_first_id + calculator_slave_count -1;
static const int nb_instances = 2;

static const float current_temperature = 20.0;

static const int NO_NEIGHBOUR_VALUE = -1;

static const int tag = 0;

/*
 * Neighbours count.
 * It could be more or less than 8 neighbours,
 * for example if plates are not squared.
 */
static const int NB_NEIGHBOURS = 8;
/*
 * Contains calculator neighbour and initial temperature
 */
typedef struct calculator_init_s {
	int neighbours_array[NB_NEIGHBOURS];
	float initial_temperature;
} calculator_init;

/*
enum message_type {
	INIT_PHASE_ENDED = 0,
	SIMULATION_PHASE_ENDED,
};
*/
static const int SIMULATION_PHASE_ENDED = -1;
static const int INIT_PHASE_ENDED = 0;

void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type);

/**
 * retrieves calculator id from given matrix dimension and row/col couple
 * e.g. given the following matrix dimension:
 * matrix_row_size = 3
 * matrix_col_size = 4
 * we would have the following matrix:
 * {
 *  {1, 2, 3, 4},
 *  {5, 6, 7, 8},
 *  {9,10,11,12},
 * }
 * row = 1 & col = 0 would return 5
 * coordinate outside the matrix would return -1
 */
int get_calculator_id(const int matrix_row_size, const int matrix_col_size, const int row, const int col);


template <class T>
void display_array(const T array[], const int array_size)
{
	cout << "{ ";
	for(int i=0; i<array_size; i++)
	{
		cout << setw(7) << array[i];
		if (i != (array_size -1))
		{
			cout << ", ";
		}
	}
	cout << " }" << endl;
}

template <class T>
void display_array(const vector<T> array)
{
    display_array(array.data(), array.size());
}


template <typename T>
void display_matrix(const vector<vector<T> > matrix)
{
	cout << "{" << endl;
	for (int row=0; row < matrix.size(); row++)
	{
		cout << "  ";
		display_array<T>(matrix[row].data(), matrix[row].size());
	}
	cout << "}" << endl;
}
void mpi_debug(const string& prog_name, const int& rank, const MPI_Comm& parent, const string& message="No message");

template<class T>
std::string t_to_string(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

float get_temperature(
        const vector<vector<float> >& temperature_matrix,
        int calculator_number);

/*
 * Given a calculators ids start from 1 and are continuous,
 * returns its row and col position in the matrix (or -1 if not found)
 * calculator_number = 5
 * matrix = {
 *      {1, 2, 3, 4},
 *      {5, 6, 7, 8},
 *      {9,10,11,12},
 * }
 * returns: row = 1 & col = 0
 */
void get_calculator_row_col(
        const int calculator_number,
        const int matrix_row_size,
        const int matrix_col_size,
        int& row,
        int& col);
#endif /* UTILS_H_ */
