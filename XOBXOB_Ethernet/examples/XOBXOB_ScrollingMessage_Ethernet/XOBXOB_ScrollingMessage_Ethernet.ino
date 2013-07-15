
////////////////////////////////////////////////////////////////////////////
//
//  XOBXOB_ScrollingMessage :: Ethernet Shield :: MAX7219 LED Matrix
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
#include <"avr/pgmspace.h">
#include "LEDMatrix7219.h"
#include "vincent90.h"

#include <XOBXOB_Ethernet.h>
#include <Ethernet.h>
#include <SPI.h>

// Ethernet shield MAC address (possibly printed on label)
byte mac[] = {0x90, 0xA2, 0xDA, 0xD0, 0x09, 0x59 };

// XOBXOB APIKey (from your XOBXOB account page)
String APIKey = "0000-0000-0000-0000-0000";

// Create XOBXOB object (for the Ethernet shield)
XOBXOB_Ethernet XOB (mac, APIKey);

// Response processing
boolean done = true;
long lastRequestTime = -20000;
String lastMessage;

long timerStart;

// Message variables
int charNum = 0, nextCharNum;
String message = " Waiting... ";

// Create the display object (use default parameters: 1, 3, 4, 5)
LEDMatrix7219 LEDMatrix(1, 15);

void setup() {

  // Open serial communications and initialize XOBXOB
  Serial.begin(9600); 
  while (!Serial);
  Serial.print ("Beginning...");
  XOB.init();
  Serial.println ("Initialized.");

  // Setting echo to "true" will print out requests and reply characters to the Serial port for debugging
  XOB.echo(false);

}

void loop() {

  ////////////////////////////////////////////////////////
  //
  // XOBXOB GET Request

  // Request every 10 seconds (but, only if done with previous request)
  if (done && ( (millis() - lastRequestTime) > 10*1000)) {

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
  
    // Load response a character at a time when it is available.
    // If true is returned, that means a completed JSON object has been received
    // If this is the first one (!done), then extract the "switch" message and 
    // check to see if we should turn the LED on
    
    while (abs(millis() - timerStart) < 75) {
      if (!done && XOB.loadStreamedResponse()) {
        message = XOB.getMessage("text");
        message = message.substring(1, message.length()-1);
        done = true;
      }
    }
  }

}


