/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 1                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          09/26/2017                                        **
     NOTE:          This program contains makefile                    **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include <math.h>     	// floor()
//#include <ctype.h>    // toupper()
//#include <unistd.h>   // Sleep

void doprocessing (int sock);						// Porcesses I/O

int main( int argc, char *argv[] ) {

	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n, pid;


	if(argc < 2)										// Validate arguments
 	{
 		printf("\nERROR: Port number is missing...\n\n\n");
 		exit(0);
 	}

	if ((atoi(argv[1]))<1024||(atoi(argv[1])>65535))	// Validate range of port#
	{
		printf("\nERROR: Invalid Port number \n\n\n");
		exit(0);
	}

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	printf("\n>> Server Started on port #: %d\n", portno);
	printf("\n>> Waiting for clients to connect... \n");
	printf("------------------------------------ \n\n");


    /* Now start listening for the clients, here
	 * process will go in sleep mode and will wait
	 * for the incoming connection
    */

	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	int counter=0;
	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(1);
		}
		else{
		counter++;
		printf(">> Client #%d is connected\n", counter);
		}

		/* Create child process */
		pid = fork();

		if (pid < 0) {
			perror("ERROR on fork");
			exit(1);
		}

		if (pid == 0) {
			/* This is the client process */
			close(sockfd);
			doprocessing(newsockfd);
				//printf("I am here %d\n",pid);
			exit(0);
		}
		else {
			close(newsockfd);
		}

	} /* end of while */
}
//------------------------------------------------------------------------

void doprocessing (int sock) {
    char buffer[256];
    do{
		int n;
		bzero(buffer,256);                 	// Reset the buffer
		n = read(sock,buffer,255);

		if (n < 0) {
			perror("ERROR reading from socket");
			exit(1);
		}

		printf("Message: %s\n",buffer);
		if(strcmp(buffer, "Bye") != 0){
			/* Reading Vowels-------------------------------------------------*/
			int i;
			int vowels=0;                    // To count # of vowels
			for(i=0; buffer[i]!='\0'; ++i)
			{                                // condition to be met for vowels
				if( buffer[i]=='a' || buffer[i]=='e' || buffer[i]=='i' ||
					buffer[i]=='o' || buffer[i]=='u' || buffer[i]=='A' ||
					buffer[i]=='E' || buffer[i]=='I' || buffer[i]=='O' ||
					buffer[i]=='U')
				{
					++vowels;                // Adds up the vowels
				}
			}								// Iterates through the buffer array

			char vowelMsg[5];              	// char array to store # of vowels
			// Getting 3 digit number system for vowel counter
			vowelMsg[2]= (char)((vowels%10)+48) ;
			vowelMsg[1]= (char)((floor((vowels/10)%10))+48) ;
			vowelMsg[0]= (char)((floor(vowels/100))+48) ;
			printf(">> The vowel count is: %s\n", vowelMsg);
			//  printf(">> Vowel count sent to the client... \n\n");
			/*--------------------------------Reading Vowels Completed -------*/


			n = write(sock,vowelMsg,3);		// Sending Vowel Count

			if (n < 0) {
				perror("ERROR writing to socket");
				exit(1);
			}
			printf(">> Vowel count sent to the client\n");
			printf("---------------------------------\n\n");
		}
		else{
			printf(">>-Client Disconnected-<<\n");
		}
		// }while(strcmp(toupper(buffer), "BYE") != 0);
	}while(strcmp(buffer, "Bye") != 0);
}
