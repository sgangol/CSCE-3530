=======================================
---------------Problem-----------------
=======================================
Create a web proxy server that can be connected by a single client and would only allow http requests. 
The proxy server should be able to cache up to five recent websites. 

=======================================
-----------Requirements---------------
=======================================
1.Create a Java based client-server architecture using sockets
2.The proxy server should be able to accept and service single client’s http requests
3.The server and client should be run on different IP and the clients where server will have fixed IP and client need not enter IP for server
4.The proxy server

=======================================
-------------Instruction---------------
=======================================

1. Compile & Execute Server
   $ bash make.sh
 [Starting Compilation]
 ----------------------
 Fetch [..OK]
 Server [..OK]
 Client [..OK]

 > COMPILATION COMPLETED!!
 -----------------------
 Server started on cse01.cse.unt.edu @ port# 5123...
 >> Waiting for the Connection................

  // Port # is Optional
  // IP address for CSE01 is hardcoded! Hence Server must run in CSE01
  // Default Port #: 5123

2. Run Client
   $ bash client.sh <port#>                 // Optional Port Number
   > Connecting with 129.120.151.94 @ Port # 5123 ...
   > CONNECTION ESTABLISHED!!

   > URL:

   // Port # is Optional
   // IP address for CSE01 is hardcoded! Hence Server must run in CSE01
   // Default Port #: 5123

3. Run Server separately
  $ bash server.sh <port#>

  Server started on cse01.cse.unt.edu @ port# 5123...
  >> Waiting for the Connection................


4. Run CLEANUP [Just in Case]
  $ bash clean.sh
