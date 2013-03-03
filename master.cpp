#include "master.h"
#include "utils.h"
#include <stdio.h>

#define NORTH			-1
#define SOUTH			 1
#define EAST			 1
#define WEST			-1

int get_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
    int north_or_south,
    int east_or_west)
{
	int neighbour = NO_NEIGHBOUR_VALUE;
	int neighbour_row = row + north_or_south;
	int neighbour_col = col + east_or_west;

	// verifies row and col couple are correct
	if((neighbour_row >= 0 && neighbour_row < matrix_row_size)
	&& (neighbour_col >= 0 && neighbour_col < matrix_col_size))
	{
		neighbour = get_calculator_id(matrix_row_size, matrix_col_size, neighbour_row, neighbour_col);
	}

	return neighbour;
}

int get_north_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = NORTH;
    int east_or_west = 0;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_north_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = NORTH;
    int east_or_west = EAST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = 0;
    int east_or_west = EAST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_south_east_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = SOUTH;
    int east_or_west = EAST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_south_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = SOUTH;
    int east_or_west = 0;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_south_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = SOUTH;
    int east_or_west = WEST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = 0;
    int east_or_west = WEST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}


int get_north_west_neighbour_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col)
{
    int north_or_south = NORTH;
    int east_or_west = WEST;

    return get_neighbour_from_matrix(
            matrix_row_size,
            matrix_col_size,
            row,
            col,
            north_or_south,
            east_or_west);
}

void get_neighbours_array_from_matrix(
	int matrix_row_size,
	int matrix_col_size,
	int row,
	int col,
	int neighbours_array[],
	int neighbours_array_size)
{
	neighbours_array[0] = get_north_neighbour_from_matrix(		// NORTH
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[1] = get_north_east_neighbour_from_matrix(	// NORTH-EAST
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[2] = get_east_neighbour_from_matrix(		// EAST
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[3] = get_south_east_neighbour_from_matrix(	// SOUTH-EAST
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[4] = get_south_neighbour_from_matrix(		// SOUTH
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[5] = get_south_west_neighbour_from_matrix(	// SOUTH-WEST
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[6] = get_west_neighbour_from_matrix(		// WEST
		matrix_row_size, matrix_col_size, row, col);
	neighbours_array[7] = get_north_west_neighbour_from_matrix(	// NORTH-WEST
		matrix_row_size, matrix_col_size, row, col);
}

void init_initial_temperature_matrix(vector<vector<float> >& matrix, const int matrix_row_size, const int matrix_col_size)
{
	vector<float> array;
	int calculator_num = calculator_slave_first_id;
	float temperature;

	for (int row=0; row < matrix_row_size; row++)
	{
		array.clear();
		for (int col=0; col < matrix_col_size; col++)
		{
            temperature = get_initial_temperature(calculator_num);
			array.push_back(temperature);
			calculator_num++;
		}
		matrix.push_back(array);
	}
}

float get_initial_temperature(int process)
{
	float initial_temperature;
    if (process == 1)
    {
        initial_temperature = 50.0;
    }
    else
    {
        initial_temperature = current_temperature;
    }

	return initial_temperature;
}

void send_init_phase_ended_message(const MPI_Comm& intercomm)
{
    int code = INIT_PHASE_ENDED;
    int myrank;
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    string code_str = t_to_string(INIT_PHASE_ENDED);
    /*
    string message = "send_init_phase_ended_message: INIT_PHASE_ENDED: " + code_str;
    mpi_debug(prog_name, myrank, parent, message);
    */
    MPI_Send(&code, 1, MPI_INT, coordinator_slave_id, tag, intercomm);
}

void wait_simulation_phase_ended_message(const MPI_Comm& intercomm)
{
	int code;
	MPI_Status status;
    int myrank;
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    string message;

	MPI_Recv(&code, 1, MPI_INT, coordinator_slave_id, tag, intercomm, &status);
    string code_str = t_to_string(code);
	if (code == SIMULATION_PHASE_ENDED)
	{  
        message = "wait_simulation_phase_ended_message: SIMULATION_PHASE_ENDED: ";
	}
	else
	{  
        message = "wait_simulation_phase_ended_message: Unexpected code: ";
	}
    message += code_str;
    mpi_debug(prog_name, myrank, parent, message);
}

MPI_Comm create_coordinator_slave_and_calculators_slaves()
{
    MPI_Comm intercomm; // communication space (parent - childs)
    int myrank;
    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	char *cmds[nb_instances] = {
		(char*)"coordinator_slave",
		(char*)"calculator_slave"
	};

	int np[nb_instances] = {
		coordinator_slave_count,	// On lance x instances du programme 1
		calculator_slave_count		// On lance y instances du programme 2
	};

	MPI_Info infos[nb_instances] = { MPI_INFO_NULL, MPI_INFO_NULL };

	int errcodes[coordinator_slave_count + calculator_slave_count]; // processes error code return

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
		errcodes // TODO: we could check the exit codes to see if everything went OK
	);

    mpi_debug(prog_name, myrank, parent, "Parent: I ran all instances.");

    return intercomm;
}

void neighbour_array_creation_and_passing(const MPI_Comm& intercomm)
{
	const int neighbours_array_size = NB_NEIGHBOURS;
	int neighbours_array[neighbours_array_size]; // neighbours array to be sent

	init_initial_temperature_matrix(initial_temperature_matrix, matrix_row_size, matrix_col_size);
	display_matrix<float>(initial_temperature_matrix);
	int calculator_row, calculator_col;
	// communication with calculators (coordinator id is 0)
	for (int dest = calculator_slave_first_id; dest <= calculator_slave_last_id; dest++)
	{
		get_calculator_row_col(dest, matrix_row_size, matrix_col_size, calculator_row, calculator_col);
		get_neighbours_array_from_matrix(
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
		calculator_init1.initial_temperature = get_temperature(initial_temperature_matrix, dest);
        /*
        string temperature_str = t_to_string(calculator_init1.initial_temperature);
        string message = "calculator_init1.initial_temperature = " + temperature_str;
        mpi_debug(prog_name, myrank, parent, message);
        */

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
	}
}

int main(int argc, char *argv[])
{
	MPI_Comm intercomm; // communication space (parent - childs)
	MPI_Init(&argc, &argv);
    prog_name = argv[0];
    MPI_Comm_get_parent(&parent);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);


    // 1 Slaves plus coordinator creation
    intercomm = create_coordinator_slave_and_calculators_slaves();

    // 2 Neighbour array and temperature creation and passing to childs
    neighbour_array_creation_and_passing(intercomm);

	// 3 End of initialisation phase
	send_init_phase_ended_message(intercomm);

	// Wait for end of simulation (sends by coordinator)
	wait_simulation_phase_ended_message(intercomm);

    mpi_debug(prog_name, myrank, parent, "Master end");

	MPI_Finalize();
	return 0;
}
