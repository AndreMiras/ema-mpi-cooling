#include "utils.h"

/*
 * Creates a type for struct calculator_init
 * TODO[perfs]: the MPI_Datatype object should be created once and saved statically
 */
void create_mpi_calculator_init_type(MPI_Datatype& mpi_calculator_init_type)
{
	const int nitems = 2;   // neighbours_array and initial_temperature
	int blocklengths[nitems] = {
		NB_NEIGHBOURS,      // each case has 8 neighbours
		1
	};
	MPI_Datatype types[nitems] = {MPI_INT, MPI_FLOAT};
	// MPI_Datatype mpi_calculator_init_type;
	MPI_Aint offsets[nitems];

	offsets[0] = offsetof(calculator_init, neighbours_array);
	offsets[1] = offsetof(calculator_init, initial_temperature);

	MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_calculator_init_type);
	MPI_Type_commit(&mpi_calculator_init_type);
}

void mpi_debug(const string& prog_name, const int& rank, const MPI_Comm& parent, const string& message)
{
    string parent_str;

    if (parent == MPI_COMM_NULL)
    {
        parent_str = "MPI_COMM_NULL";
    }
    else {
        parent_str = t_to_string(parent);
    }
    cout << "prog_name: " << prog_name.c_str() <<
            ", rank: " << rank <<
            // ", parent: " << parent_str <<
            ", message: " << message << endl;
}


// TODO[deprecated]: calculators_ids_matrix should later be computed dynamically
float get_temperature(
        const vector<vector<int> >& calculators_ids_matrix,
        const vector<vector<float> >& temperature_matrix,
        int calculator_number)
{
    int row;
    int col;
    float temperature;

    get_calculator_row_col(
            calculator_number,
            temperature_matrix.size(),
            temperature_matrix.at(0).size(),
            row,
            col);
    temperature = temperature_matrix.at(row).at(col);

    return temperature;
}

void get_calculator_row_col(
        const int calculator_number,
        const int matrix_row_size,
        const int matrix_col_size,
        int& row,
        int& col)
{
    row = -1;
    col = -1;
    if ((matrix_row_size * matrix_col_size) >= calculator_number)
    {
        row = ((calculator_number - 1) / (matrix_col_size));
        col = ((calculator_number - 1) % (matrix_col_size));
    }
}

