////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB Scrolling Message :: WiFly Shield
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
//	 IMPORTANT
//
//	 To connect to your network, insert your network SSID and PASSWORD (see note below for UNSECURED networks)
//	 To connect to your XOBXOB account insert your APIKey below (from your account Dashboard)
//

char ssid[] = "your_wifi_ssid";
char password[] = "your_wifi_password";
String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

//
///////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <WiFly.h>
#include <XOBXOB.h>

#include <LEDMatrix7219.h>
#include <vincent90.h>

// Create WiFly and XOBXOB clients
WiFlyClient wClient(XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT);
XOBXOB xClient (&wClient, APIKey);

// Response processing
boolean lastResponseReceived = true;
long lastRequestTime = -20000;
long timerStart;

// Message variables
int charNum = -1;
int nextCharNum;
String message = "Waiting...";
String newMessage;

// Create the display object (use default parameters: 1, 3, 4, 5)
LEDMatrix7219 LEDMatrix(1, 15);

void setup() {

  // Start up the WiFly and try to join the network (Keep trying every 5 seconds if unsuccessful)
  WiFly.begin();
  while (!WiFly.join(ssid, password)) delay (5000);

  // Use this line rather than the above for unsecured networks
  // while (!WiFly.join(ssid)) delay (5000);
  
  // Make a connection. Keep trying every 5 seconds if not successful.
  while (!wClient.connect()) delay (5000);

}

void loop()
{
    
  ////////////////////////////////////////////////////////
  //
  // XOBXOB GET Request

  // Request every 10 seconds (but, only if done with previous response)
  if (lastResponseReceived && ((millis() - lastRequestTime) > 10*1000)) {
 
    // Update flag and timer, and request information from XOB named "XOB"
    lastResponseReceived = false;
    lastRequestTime = millis();
    xClient.requestXOB("XOB");
    
  }

  ////////////////////////////////////////////////////////
  //
  // Display message
  
  charNum = (charNum+1) % message.length();
  nextCharNum = (charNum+1) % message.length();

  for (int column=0; column<8; column++) {
    
    timerStart = millis();
    
    int c = 0;
    for (int i=column; i<8; i++) {
      LEDMatrix.writeDeviceRegister(1, MAX7219_REG_COL0 + c, pgm_read_byte_near(*vincent90 + int(message[charNum])*8 + i) );
      c++;
    };
    for (int i=0; i<column; i++) {
      LEDMatrix.writeDeviceRegister(1, MAX7219_REG_COL0 + c, pgm_read_byte_near(*vincent90 + int(message[nextCharNum])*8 + i) );
      c++;
    };
  
    // Check the response (for 75 milliseconds).
    // "True" means a completed JSON object has been received, so extract the message
    
    while (abs(millis() - timerStart) < 75) {
      if (!lastResponseReceived && xClient.checkResponse()) {
        lastResponseReceived = true;
        newMessage = xClient.getMessage("text");
        newMessage = newMessage.substring(1, newMessage.length()-1);
        if (!message.equals(newMessage)) {
        	charNum = -1;
        	message = newMessage;
        }
      }
    }
  }

}
