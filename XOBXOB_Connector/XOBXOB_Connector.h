///////////////////////////////////////////////////////////////
//
//  XOBXOB_Connector
//
//  Arduino interface to XOBXOB IoT platform
//	For use with the Processing "connector" application
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

#ifndef _XOBXOB_Connector_h
#define _XOBXOB_Connector_h

#include <Arduino.h>
#include "XOBXOB_Info.h"
#include "FSON.h"

// CLASS
class XOBXOB_Connector
{
  
  public:

    XOBXOB_Connector	(String);               // Constructor
    void     			init();
    boolean  			connect ();
    boolean  			connected ();
    void     			stop ();
    void     			requestXOB (String);
    void				updateXOB (String, String, String);
    void     			updateXOB (String, int, String [][2]);

    void     			initResponse();
    boolean  			loadStreamedResponse();    
    String   			getMessage(String);

  private:
  
    FSON 				_FSON;                  // FSON utilities
    String 				_REQUEST_HEADER;        // XOBXOB request header

};

#endif // XOBXOB_Connector

