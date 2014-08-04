////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB Blink :: Connector
// 
//  This sketch connects to the XOBXOB IoT platform using the XOBXOB_Connector application 
//
//  The MIT License (MIT)
//  
//  Copyright (c) 2013-2014 Robert W. Gallup, XOBXOB
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

#include "XOBXOB.h"

///////////////////////////////////////////////////////////
//
// Change this for your API key (from your account dashboard)
//

String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

///////////////////////////////////////////////////////////

// Create XOBXOB object
XOBXOB xClient (&Serial, APIKey);

// Response processing
boolean lastResponseReceived = true;
long lastRequestTime = -20000;
String lastMessage;

void setup() {
  
  // Set LED pin to output. And, turn it off
  pinMode (8, OUTPUT);
  digitalWrite (8, LOW);  
  
  // Initialize Serial communication
  Serial.begin (57600);
  
}

void loop()
{
    
  // New XOB request every 4 seconds (if previous response has been received)
  if (lastResponseReceived && ((millis() - lastRequestTime) > 4*1000)) {
 
    // Update response flag and timer. Then, request information from XOB named "XOB"
    lastResponseReceived = false;
    lastRequestTime = millis();
    xClient.requestXOB("XOB");
    
  }

  // Load response a character at a time when it is available.
  // If true is returned, that means a completed JSON object has been received
  // If this is the first one (!done), then extract the "switch" message and 
  // check to see if we should turn the LED on

  if (!lastResponseReceived && xClient.checkResponse()) {

    String LED = xClient.getMessage("switch");
    if (LED == "\"ON\"") {
      digitalWrite (8, HIGH);
    } else {
      digitalWrite (8, LOW);
    }
    
    lastResponseReceived = true;
  }

}