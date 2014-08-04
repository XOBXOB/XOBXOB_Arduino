////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB Blink :: WiFly Shield
// 
//  This sketch connects to the XOBXOB IoT platform using a Sparkfun
//  WiFly shield. 
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

///////////////////////////////////////////////////////////////////////////
//
//
//   IMPORTANT
//
//   To connect to your network, insert your network SSID and PASSWORD (see note below for UNSECURED networks)
//   To connect to your XOBXOB account insert your APIKey below (from your account Dashboard)
//

char ssid[] = "your_wifi_ssid";
char password[] = "your_wifi_password";
String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

//
///////////////////////////////////////////////////////////////////////////


#include <SPI.h>
#include <WiFly.h>
#include <XOBXOB.h>

// Create WiFly and XOBXOB clients
WiFlyClient wClient(XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT);
XOBXOB xClient (&wClient, APIKey);


// Response processing
boolean lastResponseReceived = true;
long    lastRequestTime = -20000;

void setup() {
  
  // Set LED pin mode to output and turn it off
  pinMode (8, OUTPUT);
  digitalWrite (8, LOW);  
  
  // Start up the WiFly and try to join the network (poll every 5 seconds if unsuccessful)
  WiFly.begin();
  while (!WiFly.join(ssid, password)) delay (5000);

  // Use this line rather than the above for unsecured networks
  // while (!WiFly.join(ssid)) delay (5000);
  
  // Make a connection. Keep trying every 5 seconds if not successful.
  while (!wClient.connect()) delay (5000);

}

void loop()
{
    
  // New XOB request every 4 seconds (if previous response has been received)
  if (lastResponseReceived && ((millis() - lastRequestTime) > 4*1000)) {
 
    // UPdate flags and request information from XOB named "XOB"
    lastResponseReceived = false;
    lastRequestTime = millis();
    xClient.requestXOB("XOB");

  }

  // Load response a character at a time when it is available.
  // If loadStreamedResponse returns true, that means a completed response has been received
  // Extract the "switch" message and check to see if we should turn the LED on

  if (!lastResponseReceived && xClient.checkResponse()) {

    // If we have a complete one, test the "switch" value and set the LED accordingly
    lastResponseReceived = true;
    String LED = xClient.getMessage("switch");
    
    if (LED == "\"ON\"") {
      digitalWrite (8, HIGH);
    } else {
      digitalWrite (8, LOW);
    }
    
  }

}