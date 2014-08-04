////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB Blink :: Arduino Yún
// 
//  This sketch connects to the XOBXOB IoT platform using an Arduino Yún. 
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

#include <Process.h>
#include <XOBXOB.h>

///////////////////////////////////////////////////////////
//
// Change this for your APIKey
//
// NOTE: Your APIKey will be found on your account dashboard when you
// login to XOBXOB)
//

String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

///////////////////////////////////////////////////////////


// Create XOBXOB object (for the Ethernet shield)
XOBXOB xClient (APIKey);

// Variables for request timing
boolean lastResponseReceived = true;
long lastRequestTime = -20000;

void setup() {
  
  Bridge.begin();
  
  // Set the LED pin for output and turn it off
  pinMode (8, OUTPUT);
  digitalWrite (8, LOW);  
  
}

void loop()
{
    
  // New XOB request every 4 seconds (if previous response has been received)
  if (lastResponseReceived && (abs(millis() - lastRequestTime) > 4*1000)) {
 
    // Reset timer and response flags. Then, request "XOB" contents
    lastResponseReceived = false;
    lastRequestTime = millis();
    
    xClient.requestXOB("XOB");

  }

  // Check the response each time through. If a full response received, 
  // get the "switch" message from the XOB and turn the LED on/off
  if (!lastResponseReceived && xClient.checkResponse()) {

    lastResponseReceived = true;

    String LED = xClient.getMessage("switch");
    if (LED == "\"ON\"") {
      digitalWrite (8, HIGH);
    } else {
      digitalWrite (8, LOW);
    }
    
  }

}