=======================================
---------------Problem-----------------
=======================================
Implement a DHCP server using a client-server architecture

=======================================
-----------Requirements---------------
=======================================
1. Create a C/ Java based client-server architecture using UDP socket
2. The DHCP server should be able to receive messages from multiple clients
3. The server should be run on CSE01 machine and the clients should be run on any machine between CSE02 and CSE06.  The clients don’t need to broadcast the DHCP discover packet. They can use DHCP server’s IP address
4. Demonstrate that a client is requesting an IP address and DHCP server is offering an IP address from the list of currently available IP addresses
5. The DHCP server should register the client’s IP address and should acknowledge the client
6. The client should randomly generate the transaction ID. The lifetime should be set to 3600 seconds

=======================================
-------------Instruction---------------
=======================================

1. Compile
   $ make
   gcc UDPClient.c -o CLIENT
   gcc UDPServer.c -o DHCP

2. Run Server
   $ ./DHCP <port#>
   - <port#> Any VALID port #
   
3. ./CLIENT <port#>
   - same port# as the server 

4. Quit
   ^C



=======================================
-------------Project Files-------------
=======================================

- Makefile
- UDPServer.c
- UDPClient.c
- Readme.txt
- Screenshot.JPG

======================================
--- View screenshot for the  demo ---
======================================

