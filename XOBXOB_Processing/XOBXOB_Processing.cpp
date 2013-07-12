///////////////////////////////////////////////////////////////
//
//  XOBXOB_Processing.cpp
//
//  Arduino classes for communicating with XOBXOB IoT platform
//  Using the Processing internet connector application
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
#include "XOBXOB_Processing.h"

// Constructor
XOBXOB_Processing::XOBXOB_Processing(String key)
{
  // Save API key
  _APIKey = key;
  
}

// Initialize
void XOBXOB_Processing::init ()
{

  // Start the Processing connection
  Serial.begin (57600);

}

// Connect to XOBXOB server
boolean XOBXOB_Processing::connect ()
{
  // NOP
}
      
boolean XOBXOB_Processing::connected()
{
  return true;
}

// Make an HTTP GET request for XOB "x"
void XOBXOB_Processing::requestXOB (String x)
{
    String request = "GET /v1/xobs/" + x + "?key=" + _APIKey + HOST_HEADER ;
	Serial.println (request);
}

// Make an HTTP PUT request for XOB "x"
void XOBXOB_Processing::updateXOB (String x, String query)
{
    String request = "PUT /v1/xobs/" + x + "?key=" + _APIKey + '&' + query + HOST_HEADER ;
    Serial.println (request);
}

void XOBXOB_Processing::initResponse()
{
  _FSON.initStreamScanner();
}

boolean XOBXOB_Processing::loadStreamedResponse()
{
  if (Serial.available()) {
    char c = Serial.read();
    return (_FSON.setStreamedObject(c));
  } else {
    return false;
  }
}

void XOBXOB_Processing::stop()
{
  // NOP
}

String XOBXOB_Processing::getMessage(String propertyName)
{
  return (_FSON.getProperty(propertyName));
}

void XOBXOB_Processing::echo (boolean e) {
	// NOP
}