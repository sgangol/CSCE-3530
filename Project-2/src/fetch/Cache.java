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
import java.util.*;

import fetch.Response;
import fetch.Request;


public class Cache {

  private static final int CACHE_SIZE = 5;
  private static final String CACHE_PATH = "cache/";

  private static String[] cacheList = new String[CACHE_SIZE];

 // Generate a valid filename from a web request.
  public static String generateFilenameFromReq(Request req) {
    return req.getUrlAsString().split("://")[1].replace('/', '_') + ".html";
  }

  // Generate a valid cache filepath
  public static String generateCacheFilepath(String filename) {
    return CACHE_PATH + filename;
  }

// Validate URL in Cache
  public static Boolean isWebpageInCacheList(Request req) {
    String filename = generateFilenameFromReq(req);
    for (String webpage : cacheList)
      if (webpage != null)
        if (webpage.equals(filename))
          return true;
    return false;
  }

  // Return the body
  public static String getCachedWebpage(Request req)
  throws FileNotFoundException, IOException {

    String filename = generateFilenameFromReq(req);
    String path = generateCacheFilepath(filename);

    InputStream inputStream = new FileInputStream(path);
    BufferedReader buffer = new BufferedReader(new InputStreamReader(inputStream));

    String line = buffer.readLine();
    StringBuilder builder = new StringBuilder();

    while (line != null) {
      builder.append(line).append("\n");
      line = buffer.readLine();
    }

    String webpage = builder.toString();

    return webpage;
  }


   // Push a URL request to the cache list
  public static void pushToCacheList(Request req) {
    System.out.print("> Updating cache!" + System.lineSeparator() );
    String[] newCacheList = new String[CACHE_SIZE];
    newCacheList[0] = generateFilenameFromReq(req);
    for(int i = 0; i < CACHE_SIZE - 1; i++)
      newCacheList[i+1] = cacheList[i];
    cacheList = newCacheList;
  }

  // Scan for landing page& remove not in cahce list
  public static void cleanCache() {

     System.out.print("> Cleaning the cache!"  + System.lineSeparator());

    File folder = new File(CACHE_PATH);
    for (File file : folder.listFiles()) {
      Boolean found = false;
      String fileName = file.getName();
      if (fileName.contains(".html")) {
        for (String cachedName : cacheList) {
          if (cachedName != null)
            if (cachedName.contains(fileName)) found = true;
        }
        if (!found) file.delete();
      }
    }
  }

  // Create or Modify the list.txt cachefile
  public static void upsertCacheListFile() throws IOException, Exception {

    BufferedWriter writer = null;

    try {

      System.out.print("> Inserting the URL"  + System.lineSeparator() );

      StringBuilder builder = new StringBuilder();
      for (String webpage : cacheList) {
        builder.append(webpage);
        builder.append('\n');
      }

      File list = new File(generateCacheFilepath("list.txt"));

      if (list.exists()) list.delete();
      list.createNewFile();

      writer = new BufferedWriter(new FileWriter(list));
      writer.write(builder.toString());

    } finally {

      if (writer != null) writer.close();

    }

  }

  // Save WebPage
  public static void saveWebpage(Request req, Response res)
  throws IOException, Exception {

    BufferedWriter writer = null;

    try {

      System.out.print("> Saving the URL!"  + System.lineSeparator());

      String filename = generateFilenameFromReq(req);
      String path = generateCacheFilepath(filename);

      File webpage = new File(path);

      if (!webpage.exists()) webpage.createNewFile();

      writer = new BufferedWriter(new FileWriter(webpage));
      writer.write(res.getBody());

    } finally {

      if (writer != null) writer.close();

    }
  }
}
