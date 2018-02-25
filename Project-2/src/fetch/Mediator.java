/***********************************************************************
     CSCE 3530:     Computer Networks                                 **
     ASSIGNMENT:    Program Assignment 2                              **
     AUTHORS:       Srizan Gangol                                     **
     DATE:          10/21/2017                                        **
     USUAGE:        Refer to ReadMe.txt                               **
-------Read ReadMe.txt & Screenshot.JPG for instructions & demo-------**
 ***********************************************************************/

package fetch;

import java.io.*;
import java.net.*;

import fetch.Response.ResponseBuilder;
import fetch.Request.RequestBuilder;

public class Mediator {

  public static Response fetch(Request req) {

    String chunk;
    StringBuffer body = new StringBuffer();
    ResponseBuilder res = new ResponseBuilder();

    try {

      HttpURLConnection connection
      = (HttpURLConnection) req.getUrl().openConnection();

      connection.setRequestMethod(req.getMethod());

      BufferedReader data
      = new BufferedReader(new InputStreamReader(connection.getInputStream()));

      while ((chunk = data.readLine()) != null) {
        body.append(chunk);
      }

      // build response
      res.status(connection.getResponseCode());
      res.body(body.toString());

      connection.disconnect();

    } catch (Exception err) {}

    return res.build();

  }
}
