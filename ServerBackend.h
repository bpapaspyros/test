#ifndef SERVERBACKEND_H
#define SERVERBACKEND_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structs
typedef struct {
	int players;
	int quota;
	char inventory[16];
}Settings;

/*- ---------------------------------------------------------------- -*/
/**
 * @brief Initializes the the settings struct according
 * to the parameters given for later use by the server
 *
 * @param Takes in the number of parameters as well as the 
 * parameter array that was passed in to the main function
 */
 void initSettings(int argc, char **argv, Settings *s) {
	int i;					// for counter
	
	// flags we raise when we get the necessary parameters
	int gotP = 0;
	int gotQ = 0;
	int gotI = 0;

	// managing invalid parameter input
	if (argc != 7) {
		printf("Invalid parameters. Exiting ... \n");
		exit(1);		
	}

	// parsing arguments
	for(i=1; i<7; i+=2) {
		if ( !strcmp(argv[i], "-p") && gotP == 0 ) {
			s->players = atoi(argv[i+1]);
			gotP = 1; 
		} else if ( !strcmp(argv[i], "-q") && gotQ == 0 ) {
			s->quota = atoi(argv[i+1]);
			gotQ = 1;
		} else if ( !strcmp(argv[i], "-i") && gotI == 0 ) {
			strcpy(s->inventory, argv[i+1]);
			gotI = 1;
		} else {
			break;
		}
	} // for

	if (gotP && gotQ && gotI) {
		printf("\n\t Settings for this game: \n\n");
		printf("\t Players: %d \n", s->players);
		printf("\t Inventory per player: %d \n", s->quota);
		printf("\t Using %s as inventory \n\n", s->inventory);
	} else {
		printf("Invalid or missing parameters. Exiting ... \n");
		exit(1);
	}
}
/*- ---------------------------------------------------------------- -*/

#endif