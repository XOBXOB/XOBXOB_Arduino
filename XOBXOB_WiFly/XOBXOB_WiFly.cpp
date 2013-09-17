///////////////////////////////////////////////////////////////
//
//  XOBXOB_WiFly.cpp
//
//  Arduino classes for communicating with XOBXOB IoT platform
//  using a Sparkfun WiFly Shield
//
//
//  The MIT License (MIT)
//  
//  Copyright (c) 2013 Robert W. Gallup, XOBXOB
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.// 

#include <Arduino.h>
#include <XOBXOB_WiFly.h>

// Constructor
XOBXOB_WiFly::XOBXOB_WiFly(String key)
{

  // Build request header
  _REQUEST_HEADER = _LF 
  	+ "Host: " + XOBXOB_SERVER_NAME + _LF 
  	+ "APIKey: " + key + _LF
  	+ "Connection: keep-alive" + _LF + _LF;

}

// Make an HTTP GET request for XOB "x"
String XOBXOB_WiFly::requestXOB (String x)
{
    _FSON.initStreamScanner();
    String request = "GET /v1/xobs/" + x + _REQUEST_HEADER;
	return (request);
}

// Make an HTTP PUT request for a single message on XOB "x"
String XOBXOB_WiFly::updateXOB (String xobName, String messageName, String messageContent)
{

  // If the XOB or message are not specified, return. Empty messageContent is OK
  if ((xobName.length() == 0) || (messageName.length() == 0)) return (String(NULL));
  
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Return the PUT request 
  String request = "PUT /v1/xobs/" + xobName + "?" + messageName + "=" + _FSON.encodeURIComponent(messageContent) + _REQUEST_HEADER ;
  return (request);

}

// Make an HTTP PUT request for XOB "x"
String XOBXOB_WiFly::updateXOB (String x, int n, String messageList [][2])
{
  
  String query = "";
  for (int i=0; i<n; i++) {
  	query += (((i==0)?"?":"&") + messageList[i][0] + '=' + _FSON.encodeURIComponent(messageList[i][1]));
  }
  
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Return the PUT request
  String request = "PUT /v1/xobs/" + x + query + _REQUEST_HEADER ;
  return (request);

}

void XOBXOB_WiFly::initResponse()
{
  _FSON.initStreamScanner();
}

boolean XOBXOB_WiFly::loadStreamedResponse(char c)
{
    return (_FSON.setStreamedObject(c));
}

String XOBXOB_WiFly::getMessage(String messageName)
{
  return (_FSON.getProperty(messageName));
}
