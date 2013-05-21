ArduinoXOBXOBEthernet
=====================

Arduino Library for XOBXOB using the Ethernet Shield

he XOBXOB library supports the XOBXOB Internet of Things service by simplifying communication through a single Arduino object, the XOBXOB.

See the sample application XOBXOB_LightOnLightOff to see an example of how to connect your Arduino to XOBXOB. What follows is a description of the library and each of its methods.

####Create a XOBXOB object:
XOBXOB x ([mac], [APIKey])  
[mac] is the mac address of your Ethernet Shield (usually on a sticker)  
[APIKey] is the APIKey for your account. You can find it when you log into your dashboard.  

####Initialize XOBXOB  
x.init();  
This sets up subsequent use of XOBXOB

####Connect to XOBXOB
x.connect();  
returns true if successful. False otherwist.  

####Check on connection status
x.connected();  
Returns true if connected. False otherwise.  

####stop()  
x.stop();  
Stops the XOBXOB client. Usually you won't have to use theis.

####Request information from XOBXOB
x.requestXOB(XOB_Name)  
Requests information about the XOB XOB_Name

####Update information on a XOB  
x.updateXOB(XOB_Name, QueryString);  
XOB_Name is the name of the XOB. Query string is a list of properties and values, such as "passed=true"

####Init Response  
x.initResponse();  
Gets ready to receive the next response

####loadStreamedResponse()  
x.loadStreamedResponse();  
Used to get the next character in a currently streaming reply. This makes it possible to read one character at a time while performing other tasks in the main Arduino loop. Returns true when it has scanned one entire JSON object.

####echo()  
x.echo(true/false)  
Turns character echo on and off. Useful for debugging.

####getProperty()  
x.getProperty(name)  
Returns a property value from the data just received with LoadStreamed .

