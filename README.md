XOBXOB Arduino Library Guide
============================

Currently there are three Arduino XOBXOB libraries that simplify communication with the XOBXOB service. They support the Ethernet Shield, XOBXOB Connector (Net connection through the USB port with a Processing sketch), and the SparkFun WiFly shield.

Each library defines the XOBXOB object. That object is used to authenticate and send/receive messages through XOBXOB.

The Ethernet and Processing libraries are very similar. With the WiFly library, only creating requests and processing responses are handled by the library. All communication with the WiFly is handled by the WiFly library. The WiFly library supports some of the methods listed below, but not all. See the example application for for more information.

You can download the . Then, to load library in the Arduino IDE, see the instructions on http://www.Arduino.cc  

See the example application XOBXOB_blink to see samples of how to connect your Arduino to XOBXOB.
What follows is a description of the library and each of its methods.

####Create a XOBXOB object

XOBXOB_Ethernet x ([mac], [APIKey]);

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

x.updateXOB(XOB_Name, QueryString);  

XOB_Name is the name of the XOB. Query string is a list of messages and contents, such as “passed=true”. Multiple messages must be separated by an ampersand (“&”).

####Init Response  

x.initResponse();  

Gets ready to receive the next response. Before you request the contents of a XOB, you should initialize the response by calling this method. This lets XOBXOB to begin scanning for a new response object from the Internet connection.

####Load Streamed Response

x.loadStreamedResponse();  

Used to get the next character in a currently streaming reply. This makes it possible to read one character at a time while performing other tasks in the main Arduino loop. Returns true when it has scanned one entire JSON object. You can then use getMessage(), below, to retreive the contents of the message.

####Echo on/off

x.echo(true/false);

Turns character echo on and off. Useful for debugging.

####Get Message

x.getMessage(name);

Returns a message’s contents from the data just received with LoadStreamed .


