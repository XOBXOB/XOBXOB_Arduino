///////////////////////////////////////////////////////////////
//
//  XOBXOB.cpp
//
//  Arduino classes for communicating with XOBXOB IoT platform
//

#include "XOBXOB.h"
#include <Ethernet.h>
#include <SPI.h>

EthernetClient _client;                    // Ethernet client

static String _LF = "\x0A";
static String HOST_HEADER = _LF + "Host: " + XOBXOB_SERVER_NAME + _LF + _LF;

// Constructor
XOBXOB::XOBXOB(uint8_t *mac, String key)
{
  // Save mac address and API key
  _mac    = mac;
  _APIKey = key;
  
}

// Initialize the Ethernet board
void XOBXOB::init ()
{

  // Start the Ethernet connection. Delay to give it time
  Ethernet.begin(_mac);
  delay (1000);

}

// Connect to XOBXOB server
boolean XOBXOB::connect ()
{
  return(_client.connect(XOBXOB_SERVER_NAME, XOBXOB_SERVER_PORT));
}
      
boolean XOBXOB::connected()
{
  return (_client.connected());
}

// Make an HTTP GET request for XOB "x"
void XOBXOB::requestXOB (String x)
{
    String request = "GET /v1/xobs/" + x + "?key=" + _APIKey + HOST_HEADER ;
    if (_echo) {
    	Serial.println ();
    	Serial.println (request);
    }
    	
    _client.print(request);
}

// Make an HTTP PUT request for XOB "x"
void XOBXOB::updateXOB (String x, String query)
{
    String request = "PUT /v1/xobs/" + x + "?key=" + _APIKey + '&' + query + HOST_HEADER ;
    if (_echo) {
		Serial.println ();
	    Serial.println (request);
    }
    _client.print(request);
}

void XOBXOB::initResponse()
{
  _FSON.initStreamScanner();
}

boolean XOBXOB::loadStreamedResponse()
{
  if (_client.available()) {
    char c = _client.read();
    if (_echo) Serial.print(c);
    return (_FSON.setStreamedObject(c));
  } else {
    return false;
  }
}

void XOBXOB::stop()
{
  return (_client.stop());
}

String XOBXOB::getProperty(String propertyName)
{
  return (_FSON.getProperty(propertyName));
}

void XOBXOB::echo (boolean e) {
	_echo = e;
}