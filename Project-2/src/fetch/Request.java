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

public class Request {

  private URL url;
  private String method;

  public Request(RequestBuilder builder) {
    this.url = builder.url;
    this.method = builder.method;
  }

  public URL getUrl() {
    return this.url;
  }

  public String getMethod() {
    return this.method;
  }

  public String getUrlAsString() {
    return this.url.toString();
  }

  public static class RequestBuilder {
    private URL url;
    private String method;

    public RequestBuilder(String url) throws MalformedURLException {
      if (!url.contains("http")) {
        this.url = new URL("https://" + url);
      } else {
        this.url = new URL(url);
      }
      this.method = "GET";
    }

    public RequestBuilder method(String method) {
      this.method = method;
      return this;
    }

    public Request build() {
      return new Request(this);
    }

  }
}
