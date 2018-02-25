/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 3                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          11/14/2017                                        **
     USUAGE:        $ gcc -o DHCP UDPServer.c                         **
                    $ ./DHCP <port #>                                 **
     NOTE:          This program contains makefile which will compile **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUFLEN 17  //Max length of buffer
static const char timeOut[] = "3600";
void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)											// Making sure the port # exists
    {
      printf("\nSorry the port number is missing...\n");
      printf("\n [USUAGE]:$ ./DHCP <Port #>\n\n");
      exit(0);
    }

    struct sockaddr_in si_me, si_other;

    int s, i, slen = sizeof(si_other) , recv_len, portno;
    // char message[1024];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    portno = atoi(argv[1]); //The port on which to listen for incoming data

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    system("clear");
    printf("...This is UDP server...\n\n");
    // Validating IP Table file and counting the Line
    FILE *fptr;
    int totalIP = 0;  // Line counter (result)
    int counter=0;
    char c;  // To store a character read from file

    // Open the file
    fptr = fopen("IPaddress.txt", "r");

    // Check if file exists
    if (fptr == NULL)
    {
        printf("Could not open file IPaddress.txt\n");
        return 0;
    }
    printf("Initializing the IP Table!\n");
    // Extract characters from file and store in character c
    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n') // Increment count if this character is newline
            totalIP++;
    // Close the file
    fclose(fptr);
    printf("%d IP addresses loaded from the IP Table\n", totalIP);

    //keep listening for data
    while(1)
    {
        char buf[BUFLEN];
        // char timeOut[4]= "3600";
        char tmp_transID[4];
        printf("\nWaiting for client's message...\n\n");
        fflush(stdout);
        // Initializing IP Table------------------------------------------------
        FILE *fp;
        int i;

        fp = fopen("IPaddress.txt", "r");
        if (fp == NULL)
        {
          printf("Cannot open file \n");
          exit(0);
        }
        // IF IPtable is empty <EXIT>
        if(counter==totalIP) {
          printf("All %d IP Addresses for the IP Table have been assigned\n", totalIP);
          printf("No more IP Address can be assigned\n");
          printf("Ending the Server\n\n");
          close(s);

          exit(0);
        }

        // Initiating Connection------------------------------------------------
        //Receiving data from client
        bzero(buf, BUFLEN);

        // #1 DHCP Discover < INCOMING------------------------------------------
        // yoaddr: 0.0.0.0
        // Transaction ID: XXX
        // Receiving yiaddr from the client
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        //print details of the client/peer and the data received
        printf("Received packet from %s, port number:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("\nRECEIVED < DHCP DISCOVER\n");
        printf("-------------------------\n");

        printf("yiaddr: \t%s\n", buf);
        char tmp_ip[17];
        // Resetting the tmp_ip
        bzero(tmp_ip, 17);

        // Reading IP from the file
        fscanf(fp, "%s", tmp_ip);
        counter++;
        // Delete the first line of the file running the bash script
        int status = system("sed -i '1d' IPaddress.txt");


        // for(i = 0; i < counter+1; i++){
        //     fscanf(fp, "%s", tmp_ip);
        // }
        //   if (counter == ipCount){
        //     printf("No IP address Available\n");
        //     exit(0);
        //   }
        //
        // counter++;      // Line Counter
        //
        // printf("TEST %s\n", tmp_ip);
    		fclose(fp);

        // Reset buffer
        bzero(buf, BUFLEN);
        // printf("BUF AFTER CLEAN UP: \t%s\n", buf);
        // Receiving Transaction ID from the client
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        printf("Transaction ID: %s\n", buf);

        // Sending DHCP OFFER
        // YIADDR: XXX.XXX.XXX.XXX
        // Transaction ID: XXX
        // Time Out: 3600

        // Send YIADDR TO CLIENT
        printf("\nSENDING > DHCP OFFER\n");
        printf("---------------------\n");

        printf("yiaddr: \t%s\n", tmp_ip);
        printf("Transaction ID: %s\n\n", buf);
        printf("Time Out:\t%s\n", timeOut);


        if (sendto(s, tmp_ip, strlen(tmp_ip), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        // Send Transaction ID back to Client
        if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        // Send Time-out to Client
        if (sendto(s, timeOut, strlen(timeOut), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        // DONE ................................................................

        // #3 DHCP REQUEST < Incoming-------------------------------------------
        // Reset buffer
        bzero(buf, BUFLEN);
        printf("\nRECEIVED < DHCP REQUEST\n");
        printf("------------------------\n");

        // Receiving back yiaddr from the client
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        printf("yiaddr: \t%s\n", buf);
        // Send yiaddr ACK to the client
        if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        // Reset buffer
        bzero(buf, BUFLEN);
        // printf("BUF AFTER CLEAN UP: \t%s\n", buf);
        // Receiving Transaction ID from the client
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        printf("Transaction ID: %s\n", buf);
        memcpy(tmp_transID,buf,strlen(buf));
        // printf("Transaction ID: \t%s\n", tmp_transID);

        // Send Tranaction ID to the client
        if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        // Reset buffer
        bzero(buf, BUFLEN);
        // printf("BUF AFTER CLEAN UP: \t%s\n", buf);

        // Receiving Timeout
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
          printf("Time Out: \t%s\n", timeOut);
        // Sending Timeout to the Client
        if (sendto(s, timeOut, strlen(timeOut), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        printf("\nSENDING > DHCP ACK\n");
        printf("------------------\n");

        printf("yiaddr: \t%s\n", tmp_ip);
        printf("Transaction ID: %s\n", tmp_transID);
        printf("Time Out:\t%s\n", timeOut);


          // Reset buffer
          bzero(buf, BUFLEN);
    } // while

    close(s);
    return 0;
}
