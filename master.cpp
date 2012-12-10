#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
	const int nb_instances = 2;
	int i, compteur;
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

	MPI_Init( &argc, &argv );

	// On lance simultanément 2 instances de prg1 et 3 de prg2

	MPI_Comm_spawn_multiple (
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

	printf ("Pere : J'ai lance toutes les instances.\n");
	// Le père communique de façon synchrone avec chacun de
	// ses fils en utilisant l'espace de communication intercomm

	for (i=0; i<5; i++)
	{
		MPI_Send (&compteur,1,MPI_INT,i,0,intercomm);

		printf ("Pere : Envoi vers %d.\n", i);

		MPI_Recv(&compteur, 1, MPI_INT,i, 0, intercomm, &etat);

		printf ("Pere : Reception de %d.\n", i);

	}

	printf ("Pere : Fin.\n");

	MPI_Finalize();
	return 0;
}
