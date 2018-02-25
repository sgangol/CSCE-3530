/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 3                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          11/14/2017                                        **
     USUAGE:        $ gcc -o CLIENT UDPClient.c                       **
                    $ ./CLIENT <port #>                               **
     NOTE:          This program contains makefile which will compile **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>     // for srand for security

#define SERVER "129.120.151.94" //IP address of server
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
      printf("\n[USUAGE]:$ ./CLIENT <Port #>\n\n");

      exit(0);
    }
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other), portno;
    char buf[BUFLEN];
    char message[BUFLEN];
    // char timeOut[4]= "3600";
    // Generating Random Number for Transaction ID
    srand(time(NULL));
    int tID = 100+(rand()%900);   // Randomly Generate 3-digit tID
    bzero(buf, BUFLEN);

    system("clear");
    printf("...This is UDP client...\n\n");

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    portno = atoi(argv[1]); //The port on which to listen for incoming data
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(portno);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    // #1 DHCP Discover > OUTGOING--------------------------------------------
    // yoaddr: 0.0.0.0
    // Transaction ID: XXX
    // Sending yiaddr to the Server

    char yiaddr[17]="0.0.0.0";
    char tIDarray[4];
    //sprintf(tIDarray,"%d",tID);
    snprintf (tIDarray, sizeof(tIDarray), "%d", tID);
    memcpy(message,yiaddr,strlen(yiaddr));

    // Sending yiaddr to the Server
    printf("\nSENDING > DHCP DISCOVER\n");
    printf("------------------------\n");

    printf("yiaddr: \t%s\n", yiaddr);
    printf("Transaction ID: %s\n\n", tIDarray);

    if (sendto(s, yiaddr, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    // Reset buffer
    bzero(buf, BUFLEN);
    // printf("BUF AFTER CLEAN UP: \t%s\n", buf);
    // Sending Transaction ID to the Server
    if (sendto(s, tIDarray, strlen(tIDarray)+1 , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    // DONE ....................................................................

    // #2 DHCP OFFER < INCOMING-------------------------------------------------
    // yoaddr: X.X.X.X
    // Transaction ID: XXX
    // Time Out: 3600

    //Receiving reply from server and printing it
    printf("RECEIVED < DHCP OFFER\n");
    printf("---------------------\n");

    bzero(buf, BUFLEN);
    // Receiving yiaddr from the Server
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("yiaddr: \t%s\n", buf);
    // Copying ip to the yiaddr
    memcpy(yiaddr,buf,strlen(buf));

    bzero(buf, BUFLEN);
    // Receiving TranactionID from the Server
    if (recvfrom(s, buf, 4, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("Transaction ID:\t%s\n", buf);

    bzero(buf, BUFLEN);
    // Receiving TimeOut from the Server
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("Time Out:\t%s\n", buf);
    // DONE ....................................................................


    // #3 DHCP REQUEST > Outgoing-----------------------------------------------
    // yoaddr: X.X.X.X
    // Transaction ID: XXX+1
    // Time Out: 3600
    // Sending yiaddr to the Server
    tID++;
    snprintf (tIDarray, sizeof(tIDarray), "%d", tID);
    printf("\nSENDING > DHCP REQUEST\n");
    printf("----------------------\n");

    printf("yiaddr: \t%s\n", yiaddr);
    printf("Transaction ID:\t%s\n", tIDarray);

    bzero(buf, BUFLEN);

    printf("Time Out:\t%s\n", timeOut);


    if (sendto(s, yiaddr, strlen(yiaddr) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    // Incrementing Tranaction ID and sending it to the Server

    if (sendto(s, tIDarray, strlen(tIDarray), 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }

    // bzero(buf, BUFLEN);
    // Sending TimeOut to the Server
    if (sendto(s, timeOut, strlen(timeOut), 0, (struct sockaddr*) &si_other, slen) == -1)
    {
        die("sendto()");
    }
    // DONE ....................................................................


    // #4 DHCP ACK < Incoming---------------------------------------------------
    // yoaddr: X.X.X.X
    // Transaction ID: XXX+1
    // Time Out: 3600
    printf("\nRECEIVED < DHCP ACK\n");
    printf("--------------------\n");

    bzero(buf, BUFLEN);
    // Receiving yiaddr ACK from the Server
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("yiaddr: \t%s\n", buf);

    bzero(yiaddr,strlen(yiaddr));
    // Setting up yiaddr
    memcpy(yiaddr,buf,strlen(buf));

    bzero(buf, BUFLEN);
    // Receiving Tranaction ID from the server
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("Transaction ID:\t%s\n", buf);

    bzero(buf, BUFLEN);
    // Receiving TimeOut from the Server
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
    {
       die("recvfrom()");
    }
    printf("Time Out:\t%s\n", buf);
    printf("\nNEW IP ASSIGNED:%s\n\n", yiaddr);
    bzero(buf, BUFLEN);

    // Closing the socket!!
    close(s);
    return 0;
}
