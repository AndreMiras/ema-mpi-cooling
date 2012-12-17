#include <mpi.h>
#include <stdio.h>
#include <vector>

#define ARRAY_MAX_SIZE		16
#define NO_NEIGHBOUR_VALUE	-1
#define NORTH			-1
#define SOUTH			 1
#define EAST			 1
#define WEST			-1

using namespace std;

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
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + NORTH;
	int neighbour_col = col;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_north_east_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + NORTH;
	int neighbour_col = col + EAST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_east_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row;
	int neighbour_col = col + EAST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_east_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + SOUTH;
	int neighbour_col = col + EAST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + SOUTH;
	int neighbour_col = col;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_south_west_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + SOUTH;
	int neighbour_col = col + WEST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_west_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row;
	int neighbour_col = col + WEST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


/*
 * same as get_north_neighbour_from_matrix
 */
int get_north_west_neighbour_from_matrix(
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + NORTH;
	int neighbour_col = col + WEST;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = matrix[neighbour_row][neighbour_col];
	}

	return neighbour;
}


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
	vector<vector<int> > matrix,
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
	int neighbours_array[],
	int neighbours_array_size)
{
	neighbours_array[0] = get_north_neighbour_from_matrix(		// NORTH
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[1] = get_north_east_neighbour_from_matrix(	// NORTH-EAST
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[2] = get_east_neighbour_from_matrix(		// EAST
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[3] = get_south_east_neighbour_from_matrix(	// SOUTH-EAST
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[4] = get_south_neighbour_from_matrix(		// SOUTH
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[5] = get_south_west_neighbour_from_matrix(	// SOUTH-WEST
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[6] = get_west_neighbour_from_matrix(		// WEST
		matrix, matrix_row_size, matrix_col_size, row, col);
	neighbours_array[7] = get_north_west_neighbour_from_matrix(	// NORTH-WEST
		matrix, matrix_row_size, matrix_col_size, row, col);
}

/*
 * Given a calculator number, returns its row and col in the matrix (or -1 if not found)
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
	vector<vector<int> > matrix,
	const int matrix_row_size,
	const int matrix_col_size,
	int& row,
	int& col)
{
	cout << "get_calculator_row_col for calculator_number:" << calculator_number << endl;
	bool calculator_row_col_found = false;
	row = matrix_row_size;
	while (row >= 0 && !calculator_row_col_found)
	{
		col = matrix_col_size;
		row--;
		while (col >= 0 && !calculator_row_col_found)
		{
			col--;
			calculator_row_col_found = (matrix[row][col] == calculator_number);
		}
	}
	cout << "row:" << row << " col:" << col << endl;
}

void init_neighbours_array(int neighbours_array[], int neighbours_array_size)
{
	for (int i=0; i < neighbours_array_size; i++)
	{
		neighbours_array[i] = i;
	}
}

void display_matrix(const vector<vector<int> > matrix)
{
	for (int row=0; row < matrix.size(); row++)
	{
		for (int col=0; col < matrix[row].size(); col++)
		{
			cout << matrix[row][col] << "\t";
		}
		cout << endl;
	}
}

void init_matrix(vector<vector<int> >& matrix, const int matrix_row_size, const int matrix_col_size)
{
	vector<int> array;
	int calculator_num = 0;
	for (int row=0; row < matrix_row_size; row++)
	{
		array.clear();
		for (int col=0; col < matrix_row_size; col++)
		{
			array.push_back(calculator_num);
			calculator_num++;
		}
		matrix.push_back(array);
	}

}

int main(int argc, char *argv[])
{
	const int nb_instances = 2;
	MPI_Status etat;

	char *cmds[nb_instances] = {
		"dist/MPIcpp/GNU-Linux-x86/calculator_slave",
		"dist/MPIcpp/GNU-Linux-x86/calculator_slave"
	};

	int np[nb_instances] = {
		2,	// On lance 2 instances du programme 1
		3	// On lance 3 instances du programme 2
	};

	// Pas d'info supplémentaires pour contrôler le lancement
	// des programmes 1 et 2

	MPI_Info infos[nb_instances] = { MPI_INFO_NULL, MPI_INFO_NULL };

	int errcodes[5]; // Les codes de retours des 5 processus
	MPI_Comm intercomm; // L'espace de communication père - fils

	MPI_Init(&argc, &argv);

	// On lance simultanément 2 instances de prg1 et 3 de prg2

	MPI_Comm_spawn_multiple(
		// le nombre de programme (la taille des tableaux passés en paramètre).
		2,
		// la liste des programmes à exécuter.
		cmds,
		// un tableau de tableau de chaînes de caractères contenant les arguments de chaque programme.
		MPI_ARGVS_NULL,
		// le nombre maximum de processus pour chaque programme.
		np,
		// un tableau de MPI_Info pour contrôler la manière dont sont lancés les processus.
		infos,
		// le rang du processus qui exécute le spawn.
		0,
		// l'espace de communication du groupe de processus fils.
		MPI_COMM_WORLD,
		// le pointeur vers l'espace de comm entre le groupe de départ et le groupe nouvellement créé (contenant les nouveaux processus)
		&intercomm,
		// un tableau d'entier pour stocker les codes de retour de chaque processus
		errcodes
	);

	printf ("Parent: I ran all instances.\n");
	// Le père communique de façon synchrone avec chacun de
	// ses fils en utilisant l'espace de communication intercomm

	const int neighbours_array_size = 8;
	int neighbours_array[neighbours_array_size]; // neighbours array to be sent
	const int matrix_row_size = 3;
	const int matrix_col_size = 3;

	int calculator_num = 0;
	vector<vector<int> > matrix;
	init_matrix(matrix, matrix_row_size, matrix_col_size);
	display_matrix(matrix);
	int calculator_row, calculator_col;
	for (int i=0; i<5; i++)
	{
		get_calculator_row_col(i, matrix, matrix_row_size, matrix_col_size, calculator_row, calculator_col);
		get_neighbours_array_from_matrix(
				matrix,
				matrix_row_size,
				matrix_col_size,
				calculator_row,
				calculator_col,
				neighbours_array,
				neighbours_array_size);
		MPI_Send(
			// buffer représente l’adresse en mémoire du tableau de données à envoyer
			&neighbours_array,
			// nombreDeDonnees correspond à la taille de ce tableau
			neighbours_array_size,
			// typeDeDonnee permet de « typer » les données qui sont
			// envoyées vers le destinataire. Les valeurs possibles pour
			// ce paramètre sont présentées un peu plus loin.
			MPI_INT,
			// destination est le numéro du processus (ou processeur)
			// destination dans l’espace de communication considéré.
			i,
			// tag est un entier qui permet de différencier plusieurs
			// messages à destination d’un même processus (nous
			// pouvons le considérer comme un numéro de canal).
			0,
			// permet de spécifier l’ensemble des
			// processus (ou processeurs) concernés par cette
			// communication. Si tous les nœuds sont concernés alors
			// espaceDeComm vaut MPI_COMM_WORLD.
			intercomm);

		printf("Parent: Sending to %d.\n", i);

		// MPI_Recv(&compteur, 1, MPI_INT, i, 0, intercomm, &etat);
		// printf("Parent: Receiving from %d.\n", i);

	}

	printf ("Pere : Fin.\n");

	MPI_Finalize();
	return 0;
}
