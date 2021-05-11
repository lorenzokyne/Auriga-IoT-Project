/*
  MQTT.h - Library for GSM MQTT Client.
  Created by Nithin K. Kurian, Dhanish Vijayan, Elementz Engineers Guild Pvt. Ltd, July 2, 2016.
  Released into the public domain.
*/

#include "GSM_MQTT.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
extern uint8_t GSM_Response;

extern SoftwareSerial mySerial;
extern String MQTT_HOST;
extern String MQTT_PORT;

extern GSM_MQTT MQTT;
uint8_t GSM_Response = 0;
unsigned long previousMillis = 0;
//char inputString[UART_BUFFER_LENGTH];         // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
void serialEvent();
GSM_MQTT::GSM_MQTT(unsigned long KeepAlive)
{
  _KeepAliveTimeOut = KeepAlive;
}

void GSM_MQTT::begin(void)
{
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.write("AT\r\n");
  delay(1000);
  _tcpInit();
}
char GSM_MQTT::_sendAT(char *command, unsigned long waitms)
{

  unsigned long PrevMillis = millis();
  strcpy(reply, "none");
  GSM_Response = 0;
  Serial.write(command);
  unsigned long currentMillis = millis();
  //  mySerial.println(PrevMillis);
  //  mySerial.println(currentMillis);
  while ((GSM_Response == 0) && ((currentMillis - PrevMillis) < waitms))
  {
    //    delay(1);
    serialEvent();
    currentMillis = millis();
  }
  return GSM_Response;
}
char GSM_MQTT::sendATreply(char *command, char *replystr, unsigned long waitms)
{
  strcpy(reply, replystr);
  unsigned long PrevMillis = millis();
  GSM_ReplyFlag = 0;
  Serial.write(command);
  unsigned long currentMillis = millis();

  //  mySerial.println(PrevMillis);
  //  mySerial.println(currentMillis);
  while ((GSM_ReplyFlag == 0) && ((currentMillis - PrevMillis) < waitms))
  {
       delay(1);
    serialEvent();
    currentMillis = millis();
  }
  return GSM_ReplyFlag;
}
void GSM_MQTT::_tcpInit(void)
{
  switch (modemStatus)
  {
  case 0:
  {
    delay(1000);
    Serial.print("+++");
    delay(500);
    if (_sendAT("AT\r\n", 5000) == 1)
    {
      modemStatus = 1;
    }
    else
    {
      modemStatus = 0;
      break;
    }
  }
  case 1:
  {
    if (_sendAT("ATE1\r\n", 2000) == 1)
    {
      modemStatus = 2;
    }
    else
    {
      modemStatus = 1;
      break;
    }
  }
  case 2:
  {
    if (sendATreply("AT+CREG?\r\n", "0,1", 5000) == 1)
    {
      _sendAT("AT+CIPMUX=0\r\n", 2000);
      _sendAT("AT+CIPMODE=1\r\n", 2000);
      if (sendATreply("AT+CGATT?\r\n", ": 1", 4000) != 1)
      {
        _sendAT("AT+CGATT=1\r\n", 2000);
      }
      modemStatus = 3;
      _tcpStatus = 2;
    }
    else
    {
      modemStatus = 2;
      break;
    }
  }
  case 3:
  {
    if (GSM_ReplyFlag != 7)
    {
      _tcpStatus = sendATreply("AT+CIPSTATUS\r\n", "STATE", 4000);
      if (_tcpStatusPrev == _tcpStatus)
      {
        tcpATerrorcount++;
        if (tcpATerrorcount >= 10)
        {
          tcpATerrorcount = 0;
          _tcpStatus = 7;
        }
      }
      else
      {
        _tcpStatusPrev = _tcpStatus;
        tcpATerrorcount = 0;
      }
    }
    _tcpStatusPrev = _tcpStatus;
    mySerial.print(_tcpStatus);
    switch (_tcpStatus)
    {
    case 2:
    {
      _sendAT("AT+CSTT=\"AIRTELGPRS.COM\"\r\n", 5000);
      break;
    }
    case 3:
    {
      _sendAT("AT+CIICR\r\n", 5000);
      break;
    }
    case 4:
    {
      sendATreply("AT+CIFSR\r\n", ".", 4000);
      break;
    }
    case 5:
    {
      Serial.print("AT+CIPSTART=\"TCP\",\"");
      Serial.print(MQTT_HOST);
      Serial.print("\",\"");
      Serial.print(MQTT_PORT);
      if (_sendAT("\"\r\n", 5000) == 1)
      {
        unsigned long PrevMillis = millis();
        unsigned long currentMillis = millis();
        while ((GSM_Response != 4) && ((currentMillis - PrevMillis) < 20000))
        {
          //    delay(1);
          serialEvent();
          currentMillis = millis();
        }
      }
      break;
    }
    case 6:
    {
      unsigned long PrevMillis = millis();
      unsigned long currentMillis = millis();
      while ((GSM_Response != 4) && ((currentMillis - PrevMillis) < 20000))
      {
        //    delay(1);
        serialEvent();
        currentMillis = millis();
      }
      break;
    }
    case 7:
    {
      sendATreply("AT+CIPSHUT\r\n", "OK", 4000);
      modemStatus = 0;
      _tcpStatus = 2;
      break;
    }
    }
  }
  }
}

void GSM_MQTT::_ping(void)
{

  if (pingFlag == true)
  {
    unsigned long currentMillis = millis();
    if ((currentMillis - _PingPrevMillis) >= _KeepAliveTimeOut * 1000)
    {
      // save the last time you blinked the LED
      _PingPrevMillis = currentMillis;
      if (pingSent)
      {
        mySerial.println("Ping failed");
        disconnect();
        MQTT.TCP_Flag = false;
        MQTT.MQTT_Flag = false;
        MQTT.pingFlag = false;
        MQTT.sendATreply("AT+CIPSHUT\r\n", ".", 4000);
        MQTT.modemStatus = 0;
        pingSent = false;
        return;
      }
      Serial.print(char(PINGREQ * 16));
      _sendLength(0);
      pingSent = true;
      mySerial.println("pingSent = true");
    }
  }
}
void GSM_MQTT::_sendUTFString(char *string)
{
  int localLength = strlen(string);
  Serial.print(char(localLength / 256));
  Serial.print(char(localLength % 256));
  Serial.print(string);
}
void GSM_MQTT::_sendLength(int len)
{
  bool length_flag = false;
  while (length_flag == false)
  {
    if ((len / 128) > 0)
    {
      Serial.print(char(len % 128 + 128));
      len /= 128;
    }
    else
    {
      length_flag = true;
      Serial.print(char(len));
    }
  }
}
void GSM_MQTT::connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char *UserName, char *Password, char CleanSession, char WillFlag, char WillQoS, char WillRetain, char *WillTopic, char *WillMessage)
{
  ConnectionAcknowledgement = NO_ACKNOWLEDGEMENT;
  Serial.print(char(CONNECT * 16));
  char ProtocolName[7] = "MQIsdp";
  int localLength = (2 + strlen(ProtocolName)) + 1 + 3 + (2 + strlen(ClientIdentifier));
  if (WillFlag != 0)
  {
    localLength = localLength + 2 + strlen(WillTopic) + 2 + strlen(WillMessage);
  }
  if (UserNameFlag != 0)
  {
    localLength = localLength + 2 + strlen(UserName);

    if (PasswordFlag != 0)
    {
      localLength = localLength + 2 + strlen(Password);
    }
  }
  _sendLength(localLength);
  _sendUTFString(ProtocolName);
  Serial.print(char(_ProtocolVersion));
  Serial.print(char(UserNameFlag * User_Name_Flag_Mask + PasswordFlag * Password_Flag_Mask + WillRetain * Will_Retain_Mask + WillQoS * Will_QoS_Scale + WillFlag * Will_Flag_Mask + CleanSession * Clean_Session_Mask));
  Serial.print(char(_KeepAliveTimeOut / 256));
  Serial.print(char(_KeepAliveTimeOut % 256));
  _sendUTFString(ClientIdentifier);
  if (WillFlag != 0)
  {
    _sendUTFString(WillTopic);
    _sendUTFString(WillMessage);
  }
  if (UserNameFlag != 0)
  {
    _sendUTFString(UserName);
    if (PasswordFlag != 0)
    {
      _sendUTFString(Password);
    }
  }
}
void GSM_MQTT::publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message)
{
  Serial.print(char(PUBLISH * 16 + DUP * DUP_Mask + Qos * QoS_Scale + RETAIN));
  int localLength = (2 + strlen(Topic));
  if (Qos > 0)
  {
    localLength += 2;
  }
  localLength += strlen(Message);
  _sendLength(localLength);
  _sendUTFString(Topic);
  if (Qos > 0)
  {
    Serial.print(char(MessageID / 256));
    Serial.print(char(MessageID % 256));
  }
  Serial.print(Message);
}
void GSM_MQTT::publishACK(unsigned int MessageID)
{
  Serial.print(char(PUBACK * 16));
  _sendLength(2);
  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));
}
void GSM_MQTT::publishREC(unsigned int MessageID)
{
  Serial.print(char(PUBREC * 16));
  _sendLength(2);
  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));
}
void GSM_MQTT::publishREL(char DUP, unsigned int MessageID)
{
  Serial.print(char(PUBREL * 16 + DUP * DUP_Mask + 1 * QoS_Scale));
  _sendLength(2);
  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));
}

void GSM_MQTT::publishCOMP(unsigned int MessageID)
{
  Serial.print(char(PUBCOMP * 16));
  _sendLength(2);
  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));
}
void GSM_MQTT::subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS)
{
  Serial.print(char(SUBSCRIBE * 16 + DUP * DUP_Mask + 1 * QoS_Scale));
  int localLength = 2 + (2 + strlen(SubTopic)) + 1;
  _sendLength(localLength);
  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));
  _sendUTFString(SubTopic);
  Serial.print(SubQoS);
}
void GSM_MQTT::unsubscribe(char DUP, unsigned int MessageID, char *SubTopic)
{
  Serial.print(char(UNSUBSCRIBE * 16 + DUP * DUP_Mask + 1 * QoS_Scale));
  int localLength = (2 + strlen(SubTopic)) + 2;
  _sendLength(localLength);

  Serial.print(char(MessageID / 256));
  Serial.print(char(MessageID % 256));

  _sendUTFString(SubTopic);
}
void GSM_MQTT::disconnect(void)
{
  Serial.print(char(DISCONNECT * 16));
  _sendLength(0);
  pingFlag = false;
}
//Messages
const char CONNECTMessage[] PROGMEM = {"Client request to connect to Server\r\n"};
const char CONNACKMessage[] PROGMEM = {"Connect Acknowledgment\r\n"};
const char PUBLISHMessage[] PROGMEM = {"Publish message\r\n"};
const char PUBACKMessage[] PROGMEM = {"Publish Acknowledgment\r\n"};
const char PUBRECMessage[] PROGMEM = {"Publish Received (assured delivery part 1)\r\n"};
const char PUBRELMessage[] PROGMEM = {"Publish Release (assured delivery part 2)\r\n"};
const char PUBCOMPMessage[] PROGMEM = {"Publish Complete (assured delivery part 3)\r\n"};
const char SUBSCRIBEMessage[] PROGMEM = {"Client Subscribe request\r\n"};
const char SUBACKMessage[] PROGMEM = {"Subscribe Acknowledgment\r\n"};
const char UNSUBSCRIBEMessage[] PROGMEM = {"Client Unsubscribe request\r\n"};
const char UNSUBACKMessage[] PROGMEM = {"Unsubscribe Acknowledgment\r\n"};
const char PINGREQMessage[] PROGMEM = {"PING Request\r\n"};
const char PINGRESPMessage[] PROGMEM = {"PING Response\r\n"};
const char DISCONNECTMessage[] PROGMEM = {"Client is Disconnecting\r\n"};

void GSM_MQTT::printMessageType(uint8_t Message)
{
  switch (Message)
  {
  case CONNECT:
  {
    int k, len = strlen_P(CONNECTMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(CONNECTMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case CONNACK:
  {
    int k, len = strlen_P(CONNACKMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(CONNACKMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PUBLISH:
  {
    int k, len = strlen_P(PUBLISHMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PUBLISHMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PUBACK:
  {
    int k, len = strlen_P(PUBACKMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PUBACKMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PUBREC:
  {
    int k, len = strlen_P(PUBRECMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PUBRECMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PUBREL:
  {
    int k, len = strlen_P(PUBRELMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PUBRELMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PUBCOMP:
  {
    int k, len = strlen_P(PUBCOMPMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PUBCOMPMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case SUBSCRIBE:
  {
    int k, len = strlen_P(SUBSCRIBEMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(SUBSCRIBEMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case SUBACK:
  {
    int k, len = strlen_P(SUBACKMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(SUBACKMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case UNSUBSCRIBE:
  {
    int k, len = strlen_P(UNSUBSCRIBEMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(UNSUBSCRIBEMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case UNSUBACK:
  {
    int k, len = strlen_P(UNSUBACKMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(UNSUBACKMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PINGREQ:
  {
    int k, len = strlen_P(PINGREQMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PINGREQMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case PINGRESP:
  {
    pingSent = false;
    mySerial.println("pingSent = false");
    int k, len = strlen_P(PINGRESPMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(PINGRESPMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  case DISCONNECT:
  {
    int k, len = strlen_P(DISCONNECTMessage);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(DISCONNECTMessage + k);
      mySerial.print(myChar);
    }
    break;
  }
  }
}

//Connect Ack
const char ConnectAck0[] PROGMEM = {"Connection Accepted\r\n"};
const char ConnectAck1[] PROGMEM = {"Connection Refused: unacceptable protocol version\r\n"};
const char ConnectAck2[] PROGMEM = {"Connection Refused: identifier rejected\r\n"};
const char ConnectAck3[] PROGMEM = {"Connection Refused: server unavailable\r\n"};
const char ConnectAck4[] PROGMEM = {"Connection Refused: bad user name or password\r\n"};
const char ConnectAck5[] PROGMEM = {"Connection Refused: not authorized\r\n"};
void GSM_MQTT::printConnectAck(uint8_t Ack)
{
  switch (Ack)
  {
  case 0:
  {
    int k, len = strlen_P(ConnectAck0);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck0 + k);
      mySerial.print(myChar);
    }
    break;
  }
  case 1:
  {
    int k, len = strlen_P(ConnectAck1);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck1 + k);
      mySerial.print(myChar);
    }
    break;
  }
  case 2:
  {
    int k, len = strlen_P(ConnectAck2);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck2 + k);
      mySerial.print(myChar);
    }
    break;
  }
  case 3:
  {
    int k, len = strlen_P(ConnectAck3);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck3 + k);
      mySerial.print(myChar);
    }
    break;
  }
  case 4:
  {
    int k, len = strlen_P(ConnectAck4);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck4 + k);
      mySerial.print(myChar);
    }
    break;
  }
  case 5:
  {
    int k, len = strlen_P(ConnectAck5);
    char myChar;
    for (k = 0; k < len; k++)
    {
      myChar = pgm_read_byte_near(ConnectAck5 + k);
      mySerial.print(myChar);
    }
    break;
  }
  }
}
unsigned int GSM_MQTT::_generateMessageID(void)
{
  if (_LastMessaseID < 65535)
  {
    return ++_LastMessaseID;
  }
  else
  {
    _LastMessaseID = 0;
    return _LastMessaseID;
  }
}
void GSM_MQTT::processing(void)
{
  if (TCP_Flag == false)
  {
    MQTT_Flag = false;
    _tcpInit();
  }
  _ping();
}
bool GSM_MQTT::available(void)
{
  return MQTT_Flag;
}