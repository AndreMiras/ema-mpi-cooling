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

void display_matrix(const vector<vector<int> > matrix)
{
	cout << "{" << endl;
	for (int row=0; row < matrix.size(); row++)
	{
		/*
		for (int col=0; col < matrix[row].size(); col++)
		{
			cout << matrix[row][col] << "\t";
		}
		cout << endl;
		*/
		cout << "  ";
		display_array(matrix[row].data(), matrix[row].size());
	}
	cout << "}" << endl;
}

void display_array(const int array[], const int array_size)
{
	// cout << "array[" << array_size << "] = ";
	cout << "{ ";
	for(int i=0; i<array_size; i++)
	{
		// printf("array[%i]: %i\n", i, array[i]);
		cout << array[i];
		if (i != (array_size -1))
		{
			cout << ", ";
		}
	}
	cout << " }" << endl;
}
