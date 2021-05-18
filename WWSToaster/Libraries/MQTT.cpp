///Define class for MQTT
#include <SoftwareSerial.h>
#include "Arduino.h"
#include "MQTT.h"

uint8_t i = 0;
extern SoftwareSerial Serial1;
MQTT::MQTT(char *server, int port)
{
    this->server = server;
    this->port = port;
};

MQTT::MQTT(char *server, int port, Stream &out)
{
    this->OUT = &out;
    this->server = server;
    this->port = port;
};

bool MQTT::initialize()
{

    if (!sim800.initialize(1, this->OUT))
        return false;
    return sim800.startTCP(this->server, this->port);
}

bool MQTT::isConnected()
{
    return _isConnected;
}

bool MQTT::connect(const char *MQTTClientID, const char *MQTTUsername, const char *MQTTPassword)
{
    Serial1.listen();
    while (Serial1.available())
        Serial1.read();

    unsigned long datalength;
    int X;
    unsigned char encodedByte;
    OUT->println(F("Connecting to MQTT Broker..."));
    Serial1.write(0x10);
    MQTTProtocolNameLength = strlen(MQTTProtocolName);
    MQTTClientIDLength = strlen(MQTTClientID);
    MQTTUsernameLength = strlen(MQTTUsername);
    MQTTPasswordLength = strlen(MQTTPassword);

    datalength = MQTTProtocolNameLength + 2 + 4 + MQTTClientIDLength + 2 + MQTTUsernameLength + 2 + MQTTPasswordLength + 2;
    OUT->print(F("Data Length :"));
    OUT->println(datalength);
    X = datalength;
    do
    {
        encodedByte = X % 128;
        X = X / 128;
        // if there are more data to encode, set the top bit of this byte
        if (X > 0)
        {
            encodedByte |= 128;
        }

        Serial1.write(encodedByte);
    } while (X > 0);
    Serial1.write(MQTTProtocolNameLength >> 8);
    Serial1.write(MQTTProtocolNameLength & 0xFF);
    Serial1.write(MQTTProtocolName);

    Serial1.write(MQTTLVL);   // LVL
    Serial1.write(MQTTFlags); // Flags
    Serial1.write(MQTTKeepAlive >> 8);
    Serial1.write(MQTTKeepAlive & 0xFF);

    Serial1.write(MQTTClientIDLength >> 8);
    Serial1.write(MQTTClientIDLength & 0xFF);
    Serial1.print(MQTTClientID);

    Serial1.write(MQTTUsernameLength >> 8);
    Serial1.write(MQTTUsernameLength & 0xFF);
    Serial1.print(MQTTUsername);

    Serial1.write(MQTTPasswordLength >> 8);
    Serial1.write(MQTTPasswordLength & 0xFF);
    Serial1.print(MQTTPassword);

    Serial1.flush();
    OUT->println(F("Connection packet sent..."));

    return false;
}

bool MQTT::publish(const char *MQTTTopic, char *MQTTMessage, uint8_t qos)
{
    Serial1.listen();
    OUT->println(F("Publishing data..."));
    char packetid[30], str1[50], message[150];

    uint8_t datalength = 0, topiclength = 0, messagelength = 0, packetidlength = 0, X = 0;
    unsigned char encodedByte;

    // topiclength = sprintf((char *)topic, MQTTTopic);
    topiclength = strlen(MQTTTopic);
    if (qos > 0)
    {
        packetidlength = sprintf((char *)packetid, "PACKETID");
        datalength = sprintf((char *)str1, "%s%s", MQTTTopic, packetid);
    }
    else
    {
        datalength = sprintf((char *)str1, "%s", MQTTTopic);
    }
    //str1[datalength] = '\0';
    datalength = strlen(str1)+strlen(MQTTMessage);
    OUT->print(F("Datalength = "));
    OUT->println(datalength);
    OUT->print(F("str = "));
    OUT->println(MQTTMessage);

    Serial1.write(0x30 + (qos * 2)); //QOS = 1
    delay(100);
    X = (qos > 0) ? (datalength + 2 + 2) : (datalength + 2);

    do
    {
        encodedByte = X % 128;
        X = X / 128;
        // if there are more data to encode, set the top bit of this byte
        if (X > 0)
        {
            encodedByte |= 128;
        }
        Serial1.write(encodedByte);
    } while (X > 0);

    Serial1.write(topiclength >> 8);
    Serial1.write(topiclength & 0xFF);
    Serial1.print(MQTTTopic);
    OUT->print(F("topic = "));
    OUT->println(MQTTTopic);
    if (qos > 0)
    {
        Serial1.write(packetidlength >> 8);
        Serial1.write(packetidlength & 0xFF);
        Serial1.print(packetid);
    }

    messagelength = sprintf((char *)message, MQTTMessage);
    message[messagelength] = '\0';
    Serial1.print(MQTTMessage);

    OUT->print(F("message = "));
    OUT->println(MQTTMessage);
    return false;
}

bool MQTT::subscribe(char *MQTTTopic)
{
    int X = 0;
    unsigned char encodedByte;
    unsigned short topiclength;
    unsigned long datalength;
    const char MQTTPacketID = 0x0001;

    topiclength = strlen(MQTTTopic);
    datalength = 2 + 2 + topiclength + 1;

    Serial1.write(0x82);
    X = datalength;
    do
    {
        encodedByte = X % 128;
        X = X / 128;
        // if there are more data to encode, set the top bit of this byte
        if (X > 0)
        {
            encodedByte |= 128;
        }
        Serial1.write(encodedByte);
    } while (X > 0);
    Serial1.write(MQTTPacketID >> 8);
    Serial1.write(MQTTPacketID & 0xFF);
    Serial1.write(topiclength >> 8);
    Serial1.write(topiclength & 0xFF);
    Serial1.print(MQTTTopic);
    Serial1.write(MQTTQOS);
}

bool MQTT::ping()
{
    packetType = PINGREQ;
    Serial1.write(0xC0);
    Serial1.write((uint8_t)0x00);
}

bool MQTT::disconnect()
{
    return sim800.closeTCP();
}

void MQTT::loop()
{
    ping();
    serialEvent();
}

void MQTT::serialEvent()
{
    OUT->println(F("\nBegin"));
    int X;
    unsigned char code;
    unsigned char encodedByte;
    unsigned long multiplier = 1;
    int msglen = 0;
    int topiclen = 0;
    // Serial.println(Serial1.available());
    while (Serial1.available())
    {
        code = Serial1.read();

        OUT->print((char)code);
        OUT->print(F(","));
        OUT->print(code, HEX);
        OUT->print(F(","));
        OUT->println(code, DEC);

        if (code == 0x10)
        { //CONNECT packet
            while (Serial1.available())
            {
                code = Serial1.read();
                OUT->print((char)code);
            }
        }

        if (code == 0x20) //CONNACK
        {
            code = Serial1.read(); //Byte2 of CONNACK
            code = Serial1.read(); //Byte3 of CONNACK
            code = Serial1.read(); //Byte4 of CONNACK - Return Code
            if (code == 0x00)      //Successfully Connected to MQTT broker
            {
                _isConnected = true;
                OUT->println(F("Successfully Connected to MQTT broker"));
            }
            else
            {
                Serial.println(code);
                if (code == 0x01)
                    OUT->println(F("Connection Refused, unacceptable protocol version"));
                if (code == 0x02)
                    OUT->println(F("Connection Refused, identifier rejected"));
                if (code == 0x03)
                    OUT->println(F("Connection Refused, Server unavailable"));
                if (code == 0x04)
                    OUT->println(F("Connection Refused, bad user name or password"));
                if (code == 0x05)
                    OUT->println(F("Connection Refused, not authorized"));

                _isConnected = false;
                OUT->print(F("Unable to connect to MQTT broker"));
                OUT->print(F(", CONNACK received :"));
                OUT->print(code, HEX);
            }
        }

        if (code == 0x90) //SUBACK
        {
            code = Serial1.read(); //Byte2 of SUBACK
            code = Serial1.read(); //Byte3 of SUBACK
            code = Serial1.read(); //Byte4 of SUBACK
            code = Serial1.read(); //Byte5 of SUBACK
            if (code == 0x00 || code == 0x01 || code == 0x02)
                OUT->println(F("Successfully subscribed.."));
            else // When return is 0x80
                OUT->println(F("Unable to subscribe.."));
        }
        else if (code == 0xD0 || code == 0xC0)
        {
            if (code == 0xD0)
            {
                code = Serial1.read();
                if (code == 0x00)
                    _isConnected = true;
                else
                    _isConnected = false;
            }
        }
        else if (code == 0x50)
        {
            while (Serial1.available())
            {
                OUT->print((char)Serial1.read());
            }
        }
        else if (code == 0x30) //Message Received
        {
            OUT->println(F("Message Begin..."));

            do
            {
                encodedByte = Serial1.read(); //Get the Length of the message
                msglen = msglen + ((encodedByte & 127) * multiplier);
                multiplier = multiplier * 128;
                if (multiplier > 2097152) // 2097152 = 128 * 128 * 128
                {
                    OUT->println(F("Exception while calculating the Messge Length"));
                    break;
                }
            } while ((encodedByte & 128) != 0);

            code = Serial1.read(); // Topic Len MSB
            //OUT->print((char)code);OUT->print(",");OUT->println(code,HEX);

            code = Serial1.read(); // Topic Len LSB
            //OUT->print((char)code);OUT->print(",");OUT->println(code,HEX);
            topiclen = code;
            OUT->print(F("Msg Length:"));
            OUT->println(msglen, DEC);
            OUT->print(F("Topic Length:"));
            OUT->println(topiclen, DEC);
            OUT->print(F("Topic : "));
            uint8_t i = 0;
            for (i = 0; i < topiclen; i++)
            {
                OUT->print((char)Serial1.read());
            }

            OUT->print(F("\nMessage :"));

            int count = 0;
            while (Serial1.available())
            {
                code = Serial1.read();
                OUT->print((char)code);
                count++;
            }
            OUT->print(F("\nMessage Length = "));
            OUT->print(count);
            OUT->println(F("\nMessage End..."));
        }
        else if (code == 0x32)
        {
            OUT->println(F("Message packet begin"));
            while (Serial1.available())
            {
                code = Serial1.read();
                OUT->print(code);
                OUT->print(F(","));
                OUT->print(code, HEX);
                OUT->print(",");
                OUT->println((char)code);
            }
            OUT->println(F("Message packet end"));
        }
        else if (code == 0x34)
        {
            OUT->println(F("Message packet begin"));
            while (Serial1.available())
            {
                code = Serial1.read();
                OUT->print(code);
                OUT->print(",");
                OUT->print(code, HEX);
                OUT->print(",");
                OUT->println((char)code);
            }
            OUT->println(F("Message packet end"));
        }
    }
    OUT->println(F("End\n"));
}
