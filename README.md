XOBXOB Arduino Library Guide
============================

Currently there are three Arduino XOBXOB libraries that simplify communication with the XOBXOB service. They support the Ethernet Shield, XOBXOB Connector (Net connection through the USB port), and the SparkFun WiFly shield.

Each library defines the XOBXOB object. That object is used to authenticate and send/receive messages through XOBXOB.

The Ethernet and Connector libraries are very similar. With the WiFly library, only creating requests and processing responses are handled by the library. All communication with the WiFly is handled by the WiFly library. The WiFly library supports some of the methods listed below, but not all. See the example application for for more information.

You can download the Arduino zip file. Then, to install the library in the Arduino IDE, see the instructions on http://www.Arduino.cc  

See the sample project XOBXOB_blink for an example of how to connect your Arduino to XOBXOB.

What follows is a description of the library and each of its methods.

####Create a XOBXOB connection object

XOBXOB_Ethernet  x ([mac], [APIKey]);
XOBXOB_WiFly     x ([APIKey]);
XOBXOB_Connector x ([APIKey]);

“x” is any Arduino variable name (used in all subsequent calls).
[mac] is the mac address of your Ethernet Shield (usually on a sticker on the bottom of the board) .
[APIKey] is the APIKey for your account. You can find it when you log into your dashboard.  

####Initialize XOBXOB  

x.init();

This has no arguments, but sets up subsequent use of XOBXOB.

####Connect to XOBXOB

x.connect();

Returns true if successful, false otherwise.

####Check on connection status

x.connected();  

Returns true if connected, false otherwise.  

####Stop Client

x.stop();  

Stops the XOBXOB client. You usually you won’t have to use this.

####Request information from XOBXOB

x.requestXOB(XOB_Name)  

Requests information about the XOB, XOB_Name.

####Update information on a XOB  

x.updateXOB(XOB_Name, n, messageList[][2]);  

XOB_Name is the name of the XOB. The messageList is a two dimensional array with messages and contents. For each row, the first element is the message name, the second element is the message content -- both are strings. "n" is the number of messages in the list.

####Init Response  

x.initResponse();  

Clears the response buffer being filled by loadStreamedResponse(). Not usually required.

####Load Streamed Response

x.loadStreamedResponse();  

Used to get the next character in a currently streaming reply. This makes it possible to read one character at a time while performing other tasks in the main Arduino loop. Returns true when it has scanned one entire JSON object. You can then use getMessage(), below, to retreive the contents of the message.

####Get Message

x.getMessage(name);

Returns a message’s contents from the data just received with loadStreamedResponse.


