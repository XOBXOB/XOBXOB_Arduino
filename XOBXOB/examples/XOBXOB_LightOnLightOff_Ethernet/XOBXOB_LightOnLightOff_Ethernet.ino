////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB client
// 
//  This sketch connects to the XOBXOB IoT platform using an Arduino Ethernet shield. 
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

// All of these includes are required
#include <XOBXOB.h>
#include <Ethernet.h>
#include <SPI.h>

// Ethernet shield MAC address (possibly printed on label)
byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0x09, 0x59 };

// XOBXOB APIKey (from your XOBXOB account page)
String APIKey = "0000-0000-0000-0000-0000";

// Create XOBXOB object (for the Ethernet shield)
XOBXOB_Ethernet XOB (mac, APIKey);

// Response processing
boolean done = true;
long lastRequestTime = -20000;
String lastMessage;

void setup() {
  
  pinMode (8, OUTPUT);
  digitalWrite (8, LOW);  
  
  // Open serial communications and initialize XOBXOB
  Serial.begin(9600); while (!Serial);
  Serial.print ("Beginning...");
  XOB.init();
  Serial.println ("Initialized.");
  
  // Setting echo to "true" will print out requests and reply characters to the Serial port for debugging
  XOB.echo(false);
  
}

void loop()
{
    
  // Request every 4 seconds (but, only if done with previous request)
  if (done && ((millis() - lastRequestTime) > 4*1000)) {
 
    // Update done flag, and start waiting for the next interval
    // Tend to the connection and response processor
    done = false;
    if (!XOB.connected()) {
      Serial.print("Connecting...");
      XOB.connect();
      Serial.println("Done.");
    }
    XOB.initResponse();
    
    // Now, request information from XOB named "XOB"
    lastRequestTime = millis();
    XOB.requestXOB("XOB");
  }

  // Load response a character at a time when it is available.
  // If true is returned, that means a completed JSON object has been received
  // If this is the first one (!done), then extract the "switch" property and 
  // check to see if we should turn the LED on

  if (!done && XOB.loadStreamedResponse()) {

    String LED = XOB.getProperty("switch");
    if (LED == "\"ON\"") {
      digitalWrite (8, HIGH);
    } else {
      digitalWrite (8, LOW);
    }
    
    done = true;
  }

}