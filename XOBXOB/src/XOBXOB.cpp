///////////////////////////////////////////////////////////////
//
//  XOBXOB.cpp
//
//  Arduino classe for communicating with XOBXOB IoT platform using
//  any client following based on a stream
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
#include "XOBXOB.h"

////////////////////////////////////////////////////////////////
//
// Not a Yún
//
#ifndef _XOBXOB_YUN_BOARD_

// Constructor
XOBXOB::XOBXOB(void* c, String key)
{

  // Save the client
  _client = (Client *)c;

  // Build request header with API Key
  _REQUEST_HEADER = _LF
  	+ "Host: " + (String)XOBXOB_SERVER_NAME + _LF 
  	+ "APIKey: " + key + _LF
  	+ "Connection: keep-alive" + _LF + _LF;
  
}

// Connect to XOBXOB server
boolean XOBXOB::connect ()
{
  return(_client->connect(XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT));
}
      
boolean XOBXOB::connected()
{
  return (_client->connected());
}

// Make an HTTP GET request for XOB "x"
void XOBXOB::requestXOB (String x)
{
    _FSON.initStreamScanner();
    String request = "GET /v1/xobs/" + x + _REQUEST_HEADER ;    	
    _client->print(request);
}

// Make an HTTP PUT request for a single message on XOB "xobName"
void XOBXOB::updateXOB (String xobName, String messageName, String messageContent)
{

  // If the XOB or message are not specified, return. Empty messageContent is OK
  if ((xobName.length() == 0) || (messageName.length() == 0)) return;
  
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Issue the PUT request 
  String request = "PUT /v1/xobs/" + xobName + "?" + messageName + "=" + _FSON.encodeURIComponent(messageContent) + _REQUEST_HEADER ;
  _client->print(request);
}

// Make an HTTP PUT request for XOB "x"
void XOBXOB::updateXOB (String x, int n, String messageList [][2])
{
  String query = "";
  for (int i=0; i<n; i++) {
  	query += (((i==0)?"?":"&") + messageList[i][0] + '=' + _FSON.encodeURIComponent(messageList[i][1]));
  }
   
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Issue the PUT request 
  String request = "PUT /v1/xobs/" + x + query + _REQUEST_HEADER ;
  _client->print(request);
}

void XOBXOB::initResponse()
{
  _FSON.initStreamScanner();
}

boolean XOBXOB::checkResponse()
{
  if (_client->available()) {
    char c = _client->read();
    return (_FSON.setStreamedObject(c));
  } else {
    return false;
  }
}

void XOBXOB::stop()
{
  return (_client->stop());
}

String XOBXOB::getMessage(String propertyName)
{
  return (_FSON.getProperty(propertyName));
}

////////////////////////////////////////////////////////////////
//
// Yún
//
#else

// Constructor
XOBXOB::XOBXOB (String key)
{
  // Build request header
  _REQUEST_HEADER_HOST   = String("Host: ") + String(XOBXOB_SERVER_NAME);
  _REQUEST_HEADER_APIKEY = String("APIKey: ") + String(key);
  
}

// Make an HTTP GET request for XOB "x"
void XOBXOB::requestXOB (String x)
{
    _FSON.initStreamScanner();
    XOBXOB_CURL ("GET", "/v1/xobs/" + x);     
}

// Make an HTTP PUT request for a single message on XOB "xobName"
void XOBXOB::updateXOB (String xobName, String messageName, String messageContent)
{

  // If the XOB or message are not specified, return. Empty messageContent is OK
  if ((xobName.length() == 0) || (messageName.length() == 0)) return;
  
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Issue the PUT request 
  String request = "PUT /v1/xobs/" + xobName + "?" + messageName + "=" + _FSON.encodeURIComponent(messageContent);
  XOBXOB_CURL("PUT", request);

}

// Make an HTTP PUT request for XOB "x"
void XOBXOB::updateXOB (String x, int n, String messageList [][2])
{
  String query = "";
  for (int i=0; i<n; i++) {
    query += (((i==0)?"?":"&") + messageList[i][0] + '=' + _FSON.encodeURIComponent(messageList[i][1]));
  }
   
  // Initialize the stream scanner
  _FSON.initStreamScanner();
  
  // Issue the PUT request
  String request = "PUT /v1/xobs/" + x + query;
  XOBXOB_CURL("PUT", request);
    
}

boolean XOBXOB::checkResponse()
{
  if (_p.available()) {
    char c = _p.read();
    return (_FSON.setStreamedObject(c));
  } else {
    return false;
  }
}

String XOBXOB::getMessage(String propertyName)
{
  return (_FSON.getProperty(propertyName));
}

// ===========================================================

void XOBXOB::XOBXOB_CURL (String type, String request) {

    _p.begin("curl");                             // Begin curl command

    _p.addParameter ("--request");                // Request type
    _p.addParameter (type);

    _p.addParameter ("--header");                 // Header Connection:
    _p.addParameter ("Connection: keep-alive");

    _p.addParameter ("--header");                 // Header APIKey:
    _p.addParameter (_REQUEST_HEADER_APIKEY);
    
    _p.addParameter ("--header");                 // Header Host:
    _p.addParameter (_REQUEST_HEADER_HOST);

    _p.addParameter (String("http://") + XOBXOB_SERVER_NAME + request); // Add the URL

    _p.run();                                     // Run the process

}

#endif