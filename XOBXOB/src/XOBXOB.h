///////////////////////////////////////////////////////////////
//
//  XOBXOB
//
//  Arduino interface to XOBXOB IoT platform
//	For use with the Arduino Ethernet shield
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

#ifndef _xobxob_h
#define _xobxob_h

// Use this to determine if this is a Yún
#ifdef SERIAL_PORT_LINUXBRIDGE
    #define _XOBXOB_YUN_BOARD_
#endif

#include <Arduino.h>
#include "utility/FSON.h"
#include "utility/XOBXOB_Info.h"
#define _LF (String)"\x0A"

////////////////////////////////////////////////////////////////
//
// Not a Yún
//
#ifndef _XOBXOB_YUN_BOARD_

#include <Client.h>

// CLASS
class XOBXOB
{
  
  public:

                        XOBXOB (void*, String);			        // Constructor
    boolean  			connect ();								// To connect to xobxob
    boolean             connected();
    void     			stop ();								// Stops connection
    
    void     			initResponse();							// Initializes streaming buffer before sending request
    boolean  			checkResponse();						// Load response one char at a time (test for end of object)

    void     			requestXOB (String);					// Requests the contents of a XOB
    void				updateXOB (String, String, String);		// Updates a XOB with a single message
    void     			updateXOB (String, int, String [][2]);	// Updates contents of XOB with one or more messages
    String   			getMessage(String);						// Returns named message contents from FSON response
    
  private:
  
    Client *_client;											// Streaming Client
    FSON _FSON;													// FSON utilities
    String _REQUEST_HEADER;										// XOBXOB request header (set in Constructor)

};

////////////////////////////////////////////////////////////////
//
// Yún
//
#else

#include <Process.h>

// CLASS
class XOBXOB
{
  
  public:

               		XOBXOB (String);                     		// Constructor
    
    void            requestXOB (String);                        // Requests the contents of a XOB
    void            updateXOB (String, String, String);      	// Updates a XOB with a single message
    void            updateXOB (String, int, String [][2]);   	// Updates contents of XOB with one or more messages
    String          getMessage(String);                      	// Returns named message contents from FSON response
    
    boolean         checkResponse();                         	// Load response one char at a time (test for end of object)

  private:
  
    Process         _p;                                         // Process for CURL commands
    FSON            _FSON;                                   	// FSON utilities
    String          _REQUEST_HEADER_HOST;                    	// XOBXOB request header Host
    String          _REQUEST_HEADER_APIKEY;                  	// XOBXOB request header APIKey

    void            XOBXOB_CURL (String, String);				// Submits the CURL request to XOBXOB

};

#endif // _XOBXOB_YUN_BOARD_

#endif // _xobxob_h
