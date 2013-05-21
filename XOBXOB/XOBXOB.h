///////////////////////////////////////////////////////////////
//
//  xobxob
//
//  Arduino interface to XOBXOB IoT platform
//
#ifndef xobxob_h
#define xobxob_h

#include <Arduino.h>
#include <Ethernet.h>
#include "utility/FSON.h"

// XOBXOB server information
#define XOBXOB_SERVER_NAME "www.xobxob.com"
#define XOBXOB_SERVER_PORT 80

// CLASS
class XOBXOB
{
  
  public:

    XOBXOB   (uint8_t*, String);               // Constructor
    void     init();
    boolean  connect ();
    boolean  connected ();
    void     stop ();
    void     requestXOB (String);
    void     updateXOB (String, String);
    void     initResponse();
    boolean  loadStreamedResponse();
    void	 echo(boolean);
    
    String   getProperty(String);              // Returns property from FSON response

  private:
  
    uint8_t* _mac;							   // MAC Address for Ethernet card
    String   _APIKey;						   // APIKey for XOBXOB
    boolean  _echo;							   // Echos requests and read data to serial port
    FSON _FSON;                                // FSON utilities

};

#endif // xobxob

