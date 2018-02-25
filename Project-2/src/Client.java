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


public class Client
{
	private static Socket socket;

  public static void main(String args[])
  {
    try
    {
			String host = "129.120.151.94";           // HARD CODED IP address
      int port = 5123;                          // default port
      if (args.length >= 1)                     // If Port # is provided
        if (args[0] != null) port = Integer.parseInt(args[0]);      // parse the Port #


			  System.out.print("> Connecting with " + host + " @ Port # "+ port + " ..."+ System.lineSeparator() );

      InetAddress address = InetAddress.getByName(host);

      boolean active = true;

      while(active) {
        System.out.print("> CONNECTION ESTABLISHED!!" + System.lineSeparator() + System.lineSeparator() );
        System.out.print("> URL: ");
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String message = reader.readLine();

        // Connecting with the Socket
        socket = new Socket(address, port);
        DataInputStream in = new DataInputStream(socket.getInputStream());
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());

        // Sending URL to the server
				System.out.print("> Sending the request..."+ System.lineSeparator() );

        byte[] messageBuffer = new byte[256];
        messageBuffer = message.getBytes();
        out.writeInt(messageBuffer.length);
        out.write(messageBuffer);
        out.flush();

        // Receiving the message from the server
        int length = in.readInt();
        byte[] rawResponse = new byte[3000000];
        in.readFully(rawResponse, 0, length);
        String response = new String(rawResponse);

        StringBuilder output = new StringBuilder();
        output.append("> RESPONSE: ");
        output.append(response);

				System.out.print(output + System.lineSeparator() );

      }
			// Closing the connection
      socket.close();
			System.out.print("> Connection Ended!!" + System.lineSeparator() );

    }
    catch (Exception e)
    {
			System.out.print(e.toString() + System.lineSeparator() );

    }
  }
}
