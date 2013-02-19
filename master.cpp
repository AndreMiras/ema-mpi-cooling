#include "master.h"
#include "utils.h"
#include <mpi.h>
#include <stdio.h>

#define NO_NEIGHBOUR_VALUE	-1
#define NORTH			-1
#define SOUTH			 1
#define EAST			 1
#define WEST			-1

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
}

void init_neighbours_array(int neighbours_array[], int neighbours_array_size)
{
	for (int i=0; i < neighbours_array_size; i++)
	{
		neighbours_array[i] = i;
	}
}

void init_temperature_matrix(vector<vector<float> >& matrix, const int matrix_row_size, const int matrix_col_size)
{
	vector<float> array;
	int calculator_num = calculator_slave_id;
	float temperature;

	for (int row=0; row < matrix_row_size; row++)
	{
		array.clear();
		for (int col=0; col < matrix_row_size; col++)
		{
            temperature = get_initial_temperature(calculator_num);
			array.push_back(temperature);
			calculator_num++;
		}
		matrix.push_back(array);
	}
}

void init_processes_matrix(vector<vector<int> >& matrix, const int matrix_row_size, const int matrix_col_size)
{
	vector<int> array;
	int calculator_num = calculator_slave_id;

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

/*
 * Phase 3: un float correspondant à la temperature initiale du carré (fixée en dur, puis lue dans un fichier de config)
 * TODO: donner une temperature aléatoire
 */
float get_initial_temperature(int process)
{
	float initial_temperature;
    // pour le moment on donne une temperature determinée pour les tests
    // mais ça devra être aléatoire pour la suite
    if (process == 1)
    {
        initial_temperature = 50.0;
    }
    else
    {
        initial_temperature = 20.0;
    }

	return initial_temperature;
}


float get_temperature(int calculator_number)
{
    int row;
    int col;
    float temperature;

    get_calculator_row_col(
        calculator_number,
        processes_matrix,
        processes_matrix.size(),
        processes_matrix.at(0).size(),
        row,
        col);
    temperature = temperature_matrix.at(row).at(col);

    return temperature;
}


void send_init_phase_ended_message(const MPI_Comm& intercomm)
{
    int message = INIT_PHASE_ENDED;
    cout << "send_init_phase_ended_message: INIT_PHASE_ENDED: " << INIT_PHASE_ENDED << endl;
    MPI_Send(&message, 1, MPI_INT, coordinator_slave_id, tag, intercomm);
}

void wait_simulation_phase_ended_message(const MPI_Comm& intercomm)
{
	int message;
	MPI_Status status;

	MPI_Recv(&message, 1, MPI_INT, coordinator_slave_id, tag, intercomm, &status);
	if (message == SIMULATION_PHASE_ENDED)
	{  
		cout << "wait_simulation_phase_ended_message: SIMULATION_PHASE_ENDED: " << SIMULATION_PHASE_ENDED << endl;
	}
	else
	{  
		cout << "wait_simulation_phase_ended_message: Unexpected message: " << message << endl;
	}
}

MPI_Comm create_coordinator_slave_and_calculators_slaves()
{
	MPI_Status status;
	MPI_Comm intercomm; // L'espace de communication père - fils

	char *cmds[nb_instances] = {
		(char*)"coordinator_slave",
		(char*)"calculator_slave"
	};

	int np[nb_instances] = {
		coordinator_slave_count,	// On lance x instances du programme 1
		calculator_slave_count		// On lance x instances du programme 2
	};

	// Pas d'info supplémentaires pour contrôler le lancement
	// des programmes 1 et 2

	MPI_Info infos[nb_instances] = { MPI_INFO_NULL, MPI_INFO_NULL };

	int errcodes[coordinator_slave_count + calculator_slave_count]; // Les codes de retours des processus

	// On lance simultanément x instances de prg1 et y instances de prg2
	MPI_Comm_spawn_multiple(
		// le nombre de programme (la taille des tableaux passés en paramètre).
		nb_instances,
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

	printf("Parent: I ran all instances.\n");
	// Le père communique de façon synchrone avec chacun de
	// ses fils en utilisant l'espace de communication intercomm

    return intercomm;
}

void neighbour_array_creation_and_passing(const MPI_Comm& intercomm)
{
	const int neighbours_array_size = NB_NEIGHBOURS;
	int neighbours_array[neighbours_array_size]; // neighbours array to be sent

	init_temperature_matrix(temperature_matrix, matrix_row_size, matrix_col_size);
	init_processes_matrix(processes_matrix, matrix_row_size, matrix_col_size);
	cout << "processes_matrix[" << processes_matrix.size() << "][" << processes_matrix[0].size() << "] = ";
	display_matrix<int>(processes_matrix);
	cout << "temperature_matrix[" << temperature_matrix.size() << "][" << temperature_matrix[0].size() << "] = ";
	display_matrix<float>(temperature_matrix);
	int calculator_row, calculator_col;
	// on ne communique qu'avec les calculateurs (le coordinateur a l'id 0)
	for (int dest=calculator_slave_id; dest<=calculator_slave_count; dest++)
	{
		get_calculator_row_col(dest, processes_matrix, matrix_row_size, matrix_col_size, calculator_row, calculator_col);
		get_neighbours_array_from_matrix(
				processes_matrix,
				matrix_row_size,
				matrix_col_size,
				calculator_row,
				calculator_col,
				neighbours_array,
				neighbours_array_size);

		/* Creates a structure containing neighbours_array and initial_temperature to send them all in one go */

		/* creates a type for struct calculator_init */
		MPI_Datatype mpi_calculator_init_type;
		create_mpi_calculator_init_type(mpi_calculator_init_type);

		// Sets neighbours_array and initial_temperature
		calculator_init calculator_init1;
		memcpy(calculator_init1.neighbours_array, neighbours_array, neighbours_array_size * sizeof(int));
		calculator_init1.initial_temperature = get_temperature(dest);
		printf("calculator_init1.initial_temperature = %f\n", calculator_init1.initial_temperature);

        // Sends neighbours_array and initial_temperature
        MPI_Send(
                // buffer représente l’adresse en mémoire du tableau de données à envoyer
                &calculator_init1,
                // nombreDeDonnees correspond à la taille de ce tableau
                1,
                // typeDeDonnee permet de « typer » les données qui sont
                // envoyées vers le destinataire. Les valeurs possibles pour
                // ce paramètre sont présentées un peu plus loin.
                mpi_calculator_init_type,
                // destination est le numéro du processus (ou processeur)
                // destination dans l’espace de communication considéré.
                dest,
                // tag est un entier qui permet de différencier plusieurs
                // messages à destination d’un même processus (nous
                // pouvons le considérer comme un numéro de canal).
                tag,
                // permet de spécifier l’ensemble des
                // processus (ou processeurs) concernés par cette
                // communication. Si tous les nœuds sont concernés alors
                // espaceDeComm vaut MPI_COMM_WORLD.
                intercomm);
		printf("Parent: Sending to %d.\n", dest);
	}
}

int main(int argc, char *argv[])
{
	MPI_Comm intercomm; // L'espace de communication père - fils
	MPI_Init(&argc, &argv);

    // 1 Slaves plus coordinator creation
    intercomm = create_coordinator_slave_and_calculators_slaves();

    // 2 Neighbour array and temperature creation and passing to childs
    neighbour_array_creation_and_passing(intercomm);

	// 3 fin de la phase d'initialisation
	send_init_phase_ended_message(intercomm);

	// Attend la fin de la simulation (message envoyé par le coordinateur
	wait_simulation_phase_ended_message(intercomm);

	printf ("Pere : Fin.\n");

	MPI_Finalize();
	return 0;
}
