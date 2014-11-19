/**
 * @file Client.c
 * @author Vaios Papaspyros
 * 
 * @brief Implemenation of the game's client
 *
 * In this file the player (client) is created. We make contact with
 * the server and get its response concerning the room the player 
 * must be assigned in. We also check his quota and its validity.
 *
 */

#include "SharedHeader.h"
#include "ClientBackend.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ  27

void makeHandshake(int s);

int main(int argc, char **argv) {
	cSettings set;					// player settings

	int sockfd;						// socket
	struct sockaddr_un servaddr;	// struct for server address
	int pid;						// pid

	// getting parameters to set up the server according to the user
	initcSettings(argc, argv, &set);

	// initializing connection variables
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0); // client endpoint
	bzero(&servaddr, sizeof(servaddr)); 	   // zero servaddr fields
	servaddr.sun_family = AF_LOCAL;			   // setting the socket type to local
	strcpy(servaddr.sun_path, SRV_PATH);  	   // define the name of this socket


/*- ------------------- testing ------------------- */
	// connect the client's and server's endpoints
	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	int j = 0;
	char send;
	int getID;

	// printing player name so that we know he is connected
	for (j=0; j<strlen(set.name); j++ ) {

		if (feof(stdin) ) {
			break;
		}

		send = set.name[j];
		write(sockfd, &send, sizeof(char));
	}

	send = '\n';
	write(sockfd, &send, sizeof(char));

	// while( getchar() != '\n' ) {

	// }

	read(sockfd, &getID, sizeof(int));

	printf("assigned id: %d\n", getID);

	// if (read(connfd, &get, sizeof(int)) > 0) {
	// 	if (getID != -1) {
	// 		set.roomID = getID;
	// 	}
	// }


	close(sockfd);
/*- ------------------- testing ------------------- */

	return 0;
}

