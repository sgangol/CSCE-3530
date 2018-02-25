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

public class Response {

  private int status;
  private String body;

  private Response(ResponseBuilder builder) {
    this.status = builder.status;
    this.body = builder.body;
  }

  public int getStatus() {
    return this.status;
  }

  public String getBody() {
    return this.body;
  }

  public static class ResponseBuilder {
    private int status;
    private String body;

    public ResponseBuilder() {}

    public ResponseBuilder status(int status) {
      this.status = status;
      return this;
    }

    public ResponseBuilder body(String body) {
      this.body = body;
      return this;
    }

    public Response build() {
      return new Response(this);
    }

  }
}
