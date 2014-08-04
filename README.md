XOBXOB Arduino Library Guide
============================

There is one Arduino XOBXOB library that simplifies communication with the XOBXOB service. It generally supports shields that can be accessed as Serial objects, the XOBXOB Connector (Net connection through the USB port), and the Arduino Yún.

The library defines the XOBXOB object. That object is used to authenticate and send/receive messages through XOBXOB.

*Note: This library uses the new library structure introduced in Arduino 1.5 and will not work correctly in earlier versions. V1.5.7 also supports the Arduino Yún.*

####To install the XOBXOB library

1) Download the Arduino zip file.
2) Refer to the instructions on http://www.arduino.cc to install the library in the Arduino IDE (http://arduino.cc/en/Guide/Libraries).

####Running a test project

See the sample project XOBXOB_blink for an example of how to connect your Arduino to XOBXOB.

####Other resources

There are several examples included with the library. You can find them through the *Files > Examples > XOBXOB* menu in the Arduino IDE.

---
#XOBXOB Library Reference

This section describes library methods in more detail.

####Create a XOBXOB connection object

For most connection methods:

*XOBXOB  x(s, APIKey);*

*x* -- Any Arduino variable name (used in subsequent references).  
*s* -- The connector object, e.g. Serial, Ethernet, etc.
*APIKey* -- is the APIKey for your account. You can find it when you log into your dashboard.  

####Connect to XOBXOB

*x.connect();*

Returns true if connecting to XOBXOB was successful, false otherwise.

####Check on connection status

*x.connected();*  

Returns true if connecting to XOBXOB was successful, false otherwise.

####Stop Client

*x.stop();*  

Stops the XOBXOB client. You usually you won’t have to use this.

####Request information from XOBXOB

*x.requestXOB(XOB_Name)*  

Requests information about the XOB, XOB_Name.

####Update information on a XOB  

*x.updateXOB(XOB_Name, messageName, messageContent);*  

Updates a single message in a XOB. XOB_Name is the name of the XOB. The messageName is the name of a single message in the XOB. messageContent is the String content of the message.

*x.updateXOB(XOB_Name, n, messageList[][2]);*  

Updates one or more messages in a XOB. XOB_Name is the name of the XOB. The messageList is a two dimensional array with messages and contents. For each row, the first element is the message name, the second element is the message content -- both are strings. "n" is the number of messages in the list. Generally the other form of the updateXOB method is easier to use.

####Init Response  

*x.initResponse();*  

Clears the response buffer being filled by loadStreamedResponse(). Not usually required.

####Check Response

*x.checkResponse();*  

Used to get the next character in a reply. This makes it possible to read one character at a time while performing other tasks in the main Arduino loop. Returns true when it has received one entire JSON object. You can then use getMessage(), below, to retreive the contents of the message.

####Get Message

x.getMessage(name);

Returns a message’s contents from the data just received with *checkResponse()*.

---
#XOBXOB Library Reference -- Yún

This section describes library methods in more detail.

####Create a XOBXOB connection object

For most connection methods:

*XOBXOB  x(APIKey);*

*x* -- is any Arduino variable name (used in subsequent references).  
*APIKey* -- is the APIKey for your account. You can find it when you log into your dashboard.  

####Request information from XOBXOB

*x.requestXOB(XOB_Name)*  

Requests information about the XOB, XOB_Name.

####Update information on a XOB  

*x.updateXOB(XOB_Name, messageName, messageContent);*  

Updates a single message in a XOB. XOB_Name is the name of the XOB. The messageName is the name of a single message in the XOB. messageContent is the String content of the message.

*x.updateXOB(XOB_Name, n, messageList[][2]);*  

Updates one or more messages in a XOB. XOB_Name is the name of the XOB. The messageList is a two dimensional array with messages and contents. For each row, the first element is the message name, the second element is the message content -- both are strings. "n" is the number of messages in the list. Generally the other form of the updateXOB method is easier to use.

####Check Response

*x.checkResponse();*  

Used to get the next character in a reply. This makes it possible to read one character at a time while performing other tasks in the main Arduino loop. Returns true when it has received one entire JSON object. You can then use getMessage(), below, to retreive the contents of the message.

####Get Message

x.getMessage(name);

Returns a message’s contents from the data just received with *checkResponse()*.


