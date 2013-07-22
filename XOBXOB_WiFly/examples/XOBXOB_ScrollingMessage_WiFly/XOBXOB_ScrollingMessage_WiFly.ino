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
//	 To connect to YOUR network,
//	 set network SSID and PASSWORD in credentials.h
//
//	 See the note below for UNSECURED networks
//
//	 Also, add your APIKey below (from your account Dashboard)

#include "credentials.h"
String APIKey = "xxxx-xxxx-xxxx-xxxx-xxxx";

//
///////////////////////////////////////////////////////////////////////////

#include "credentials.h"

// Other Includes
#include <WiFly.h>
#include "XOBXOB_WiFly.h"
#include <"avr/pgmspace.h">
#include "LEDMatrix7219.h"
#include "vincent90.h"

// Create XOBXOB_WiFly and WiFly Client
XOBXOB_WiFly XOB (APIKey);
Client WiFlyClient (XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT);

// Response processing
boolean lastResponseReceived = true;
long lastRequestTime = -20000;
long timerStart;

// Message variables
int charNum = -1;
int nextCharNum;
String message = " Waiting... ";
String newMessage;

// Create the display object (use default parameters: 1, 3, 4, 5)
LEDMatrix7219 LEDMatrix(1, 15);

void setup() {
  
  // Start up the WiFly
  WiFly.begin();
  
  // Try to join network
  if (!WiFly.join(ssid, password)) {				// for SECURED NETWORK
  //if (!WiFly.join(ssid)) {					// for UNSECURED NETWORK

    while (1);
  }  

  // Connect to xobxob.com
  WiFlyClient.connect();
  
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
    WiFlyClient.println(XOB.requestXOB("XOB"));
    
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
  
    // Loop for 75 milliseconds loading response a character at a time when it is available
    // (this is so we can load the response faster during frames of the message animation)
    // If loadStreamedResponse(c) is true, a completed object has been received
    // So, set the lastResponseReceived flag to true and extract the new message
    // If the new message is different from the previous one, switch to the new message
    while (abs(millis() - timerStart) < 75) {
      if (WiFlyClient.available()) {
        char c = WiFlyClient.read();
        if (!lastResponseReceived && XOB.loadStreamedResponse(c)) {
          lastResponseReceived = true;
          newMessage = XOB.getMessage("text");
          newMessage = newMessage.substring(1, newMessage.length()-1);
          if (!message.equals(newMessage)) {
          	charNum = -1;
          	message = newMessage;
          }
        }
      }
    }
  }

}
