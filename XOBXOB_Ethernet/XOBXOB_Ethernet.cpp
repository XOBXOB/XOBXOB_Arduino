///////////////////////////////////////////////////////////////
//
//  XOBXOB_Ethernet.cpp
//
//  Arduino classes for communicating with XOBXOB IoT platform
//  Using an Arduino Ethernet Shield
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
#include "XOBXOB_Ethernet.h"

EthernetClient _client;                    // Ethernet client

// Constructor
XOBXOB_Ethernet::XOBXOB_Ethernet(uint8_t *mac, String key)
{
  // Save mac address and API key
  _mac    = mac;
  _APIKey = key;
  
}

// Initialize the Ethernet board
void XOBXOB_Ethernet::init ()
{

  // Start the Ethernet connection. Delay to give it time
  Ethernet.begin(_mac);
  delay (1000);

}

// Connect to XOBXOB server
boolean XOBXOB_Ethernet::connect ()
{
  return(_client.connect(XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT));
}
      
boolean XOBXOB_Ethernet::connected()
{
  return (_client.connected());
}

// Make an HTTP GET request for XOB "x"
void XOBXOB_Ethernet::requestXOB (String x)
{
    String request = "GET /v1/xobs/" + x + "?key=" + _APIKey + HOST_HEADER ;
    if (_echo) {
    	Serial.println ();
    	Serial.println (request);
    }
    	
    _client.print(request);
}

// Make an HTTP PUT request for XOB "x"
void XOBXOB_Ethernet::updateXOB (String x, String query)
{
    String request = "PUT /v1/xobs/" + x + "?key=" + _APIKey + '&' + query + HOST_HEADER ;
    if (_echo) {
		Serial.println ();
	    Serial.println (request);
    }
    _client.print(request);
}

void XOBXOB_Ethernet::initResponse()
{
  _FSON.initStreamScanner();
}

boolean XOBXOB_Ethernet::loadStreamedResponse()
{
  if (_client.available()) {
    char c = _client.read();
    if (_echo) Serial.print(c);
    return (_FSON.setStreamedObject(c));
  } else {
    return false;
  }
}

void XOBXOB_Ethernet::stop()
{
  return (_client.stop());
}

String XOBXOB_Ethernet::getMessage(String propertyName)
{
  return (_FSON.getProperty(propertyName));
}

void XOBXOB_Ethernet::echo (boolean e) {
	_echo = e;
}