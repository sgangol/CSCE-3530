/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 2                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          10/21/2017                                        **
     USUAGE:        Refer to ReadMe.txt                               **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/


import java.io.*;
import java.net.*;

import fetch.*;

public class Server
{

  public static final int OK = 200;
  public static final int DEFAULT_PORT = 5123;    // Defailt Port #
  public static final int MESSAGE_SIZE = 256;
  public static final int PAYLOAD_SIZE = 3000000;

  private static Socket socket;

  public static void main(String[] args) {

    try {

      // Connecting with the client
      int port = DEFAULT_PORT;

      if (args.length >= 1)
        if (args[0] != null) port = Integer.parseInt(args[0]);

      ServerSocket serverSocket = new ServerSocket(port);
      System.out.print("Server started on cse01.cse.unt.edu @ port# " + port + "..." + System.lineSeparator());

			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			int length;

      // Server is always listening!!!
      while(true)
      {
        // connect to the client
          System.out.print(">> Waiting for the Connection................" + System.lineSeparator());
				socket = serverSocket.accept();

				DataInputStream in = new DataInputStream(socket.getInputStream());
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());

				// read message from client
				length = in.readInt();
				byte[] rmessage = new byte[MESSAGE_SIZE];
				in.readFully(rmessage, 0, length);
        String recvMessage = new String(rmessage);

        System.out.print("> Building web request..." + System.lineSeparator());

        Request req = new Request.RequestBuilder(recvMessage.trim())
          .method("GET")
          .build();

        // check if the webpage is cached
        String webpage = "> ERROR!! Unknown proxy";

        System.out.print("> Verifying cache for " + req.getUrlAsString() + "!" + System.lineSeparator());

        if (Cache.isWebpageInCacheList(req)) {
          System.out.print("> URL is cached!" + System.lineSeparator() );

          webpage = Cache.getCachedWebpage(req);
        } else {
          System.out.print("> URL has not been cached, fetching webpage..." + System.lineSeparator() );

          Response res = Mediator.fetch(req);
          if (res.getStatus() != OK) {
            // Forwarding http call response to the client
            System.out.print("HTTP Status Code: " + res.getStatus() + System.lineSeparator() );

            webpage = "> HTTP Status is not 200. Unable to fulfill request.";
          } else {
            System.out.print("> HTTP Status Code: " + res.getStatus()+ System.lineSeparator() );

            // Caching the URL
            System.out.print("> Caching the URL!"+ System.lineSeparator()) ;

            Cache.pushToCacheList(req);
            Cache.cleanCache();
            Cache.upsertCacheListFile();
            Cache.saveWebpage(req, res);
            webpage = res.getBody();
          }

        }
        System.out.print("> Preparing the payload!"+ System.lineSeparator() );

        byte[] payload = new byte[PAYLOAD_SIZE];
        payload = webpage.getBytes();

				out.writeInt(payload.length);
				out.write(payload);
        out.flush();
        System.out.print("> Sent to the client!"+ System.lineSeparator() );

        socket.close();                     // Closing the socket
      }
    } catch (Exception e) {

      StringBuilder errorMessage = new StringBuilder();
      StringWriter errors = new StringWriter();
      e.printStackTrace(new PrintWriter(errors));

      errorMessage.append("An exception has been caught...\n");
      errorMessage.append(errors.toString());

      System.out.print(errorMessage);         // ERROR!!!

    } finally {

    }
  }
}
