=======================================

-------------Instruction---------------

=======================================



1. Compile

   $ make
   gcc client.c -o client
   gcc server.c -o server -lm

2. Run Server

   $ ./server <port#>
   - <port#> Any VALID port #

3. ./client <port#>

   - same port# as the server 

4. Send Message [Client]

   > <user input string>

5. Receive vowel count [Client]

   > The number of vowels present is XXX

6. Quit [Client]
   
> Bye


7. Quit [Server]

   > ^C

=======================================

-------------Project Files-------------

=======================================



- Makefile
- server.c
- client.c
- Readme.txt
- Screenshot.JPG

======================================
--- View screenshot for the  demo ---
======================================

Problem:
Write a client and a server program where the server can be connected by multiple clients. The clients will send a message (a complete sentence) to the server and the server will count the total number of vowels present in that message and will return that number to the client. The client will print that number. If the client wants to close the connection, it will send “Bye” message to the server. Upon receiving that message, the server will close that particular connection.
