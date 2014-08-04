////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB Blink :: Ethernet Shield
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

#include <SPI.h>
#include <Ethernet.h>
#include <XOBXOB.h>

///////////////////////////////////////////////////////////
//
// Change these for your Ethernet Shield and your APIKey
//
// NOTE: the MAC address for your Ethernet Shield might be
// printed on a label on the bottom of the shield. Your
// APIKey will be found on your account dashboard when you
// login to XOBXOB)
//

byte mac[]    = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

///////////////////////////////////////////////////////////

// Create ethernet and XOBXOB clients
EthernetClient eClient;
XOBXOB xClient (&eClient, APIKey);

// Variables for request timing
boolean lastResponseReceived = true;
long lastRequestTime = -20000;

void setup() {
  
  // Turn LED off to start
  pinMode (8, OUTPUT);
  digitalWrite (8, LOW);  
  
  // Begin Ethernet. If not successful, flash LED and hang
  if (Ethernet.begin(mac) == 0) {
    byte light = 0; while (true) {digitalWrite (8, light^=1); delay (100);}
  }

}

void loop()
{
    
  // New XOB request every 4 seconds (if previous response has been received)
  if (lastResponseReceived && (abs(millis() - lastRequestTime) > 4*1000)) {
 
    // Connect to XOBXOB, if necessary
    while (!xClient.connected()) xClient.connect();

    // Reset timer and response flags. Then, request "XOB" contents
    lastResponseReceived = false;
    lastRequestTime = millis();
    xClient.requestXOB("XOB");

  }

  // Check for a response
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