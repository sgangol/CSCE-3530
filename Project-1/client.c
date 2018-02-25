/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 1                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          09/26/2017                                        **
     NOTE:          This program contains makefile                    **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/

// Line #37 for IP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];										// Max 256 char

	if (argc < 2)											// Making sure the port # exists
	{
		printf("\nPort number is missing...\n");
		exit(0);
	}

	portno = atoi(argv[1]);									// Converting the input to int
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)											// If connection fails
		error(EXIT_FAILURE, 0, "ERROR opening socket");
	server = gethostbyname(""); 							//<<<<<<<<<<<<<<<<<<<<<<<<<< Update IP Address here		
	//server = gethostbyname("localhost"); 					// Both in the same machine [IP address 127.0.0.1]

	if (server == NULL)										// If server not found
	{
		printf("\nERROR, no such host...\n");
		exit(0);
	}

	// Connecting with the server
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	memcpy(&serv_addr.sin_addr, server->h_addr, server->h_length);
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		error(EXIT_FAILURE, 0, "ERROR connecting the server...");

	//Sending the message to the server
	do{													// Loop until "Bye"
		printf("\n> ");
		bzero(buffer,256);
			//printf("\n Buffer should be RESET: %s\n", buffer);
			//scanf("%s", buffer);						// Breaks in the first White Space
		scanf ("%[^\n]%*c", buffer);					// Accepts White Spaces
			//printf("%s",buffer);						//Testing input

		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
		{
			error(EXIT_FAILURE, 0, "ERROR writing to socket");
		}
		if(strcmp(buffer, "Bye") != 0){
				//Receiving the message from the client
				bzero(buffer,256);
					// printf("\n Buffer should be RESET: %s\n", buffer);
				n = read(sockfd, buffer, 255);
				if (n < 0)
					error(EXIT_FAILURE, 0, "ERROR reading from socket");
				else
				{
					printf("The number of vowels present is %s\n", buffer);
				}
		}

	}while(strcmp(buffer, "Bye") != 0);
	//Closing the connection
	close(sockfd);

	return 0;
}
