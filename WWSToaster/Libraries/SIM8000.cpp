///Define class for MQTT

#include "Arduino.h"
#include "SIM8000.h"
#include <SoftwareSerial.h>

SoftwareSerial Serial1(7, 6);

bool SIM8000::checkModem()
{
  if (sendATcommand((char*)"AT\r", (char*)"OK", 500) == 0)
    return false;
  return true;
};

SIM8000::SIM8000()
{
  pinMode(RESET_PIN, OUTPUT);
};

SIM8000::SIM8000(Stream &out)
{
  this->OUT = &out;
}

bool SIM8000::initialize(uint8_t mode, Stream *out)
{
  this->OUT = out;
  //(Serial)this->OUT.begin(9600);
  Serial1.begin(9600);
  uint8_t retryCount = 0;
  this->mode = mode;
  while (!checkNetwork())
  {
    delay(100);
  }
  if (!initModem())
  {
    OUT->println(F("Modem initialize failed.."));
    return false;
  }

  while (retryCount < 5)
  {
    if (initNetwork())
      break;
    OUT->println(F("Network initialize failed.."));
    retryCount++;
  }

  if (!initGPRS())
  {
    OUT->println(F("GPRS initialize failed.."));
    return false;
  }
  return true;
}

bool SIM8000::initModem()
{
  uint8_t tryCount = 0;
  resetModem();
  while (1)
  {
    if (checkModem())
      break;
    if (tryCount > 5)
      return false;
    tryCount++;
  }

  if (sendATcommand((char*)"ATE0\r", (char*)"OK", 1000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CFUN?\r", (char*)"+CFUN: 1", 1000) == 0)
    return false;
  if (!checkNetwork())
    return false;
#ifdef debug
  OUT->println(F("Modem initialized successfully..."));
#endif
  return true;
};

bool SIM8000::initNetwork()
{
  if (this->mode == 0)
  { //MODE = 0
    if (sendATcommand((char*)"AT+CIPMODE=0\r", (char*)"OK", 1000) == 0)
      return false;
  }
  else
  { // MODE = 1
    if (sendATcommand((char*)"AT+CIPMODE=1\r", (char*)"OK", 1000) == 0)
      return false;
  }
  if (sendATcommand((char*)"AT+CIPSRIP=0\r", (char*)"OK", 1000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CGATT?\r", (char*)"+CGATT: 1", 5000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CIPSTATUS\r", (char*)"INITIAL", 5000) == 0)
    return false;

  OUT->println(F("Network Initialized..."));
  return true;
}

bool SIM8000::initGPRS()
{
  if (sendATcommand((char*)"AT+CSTT=\"mobile.vodafone.it\",\"\",\"\"\r", (char*)"OK", 30000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CIPSTATUS\r", (char*)"START", 2000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CIICR", (char*)"OK", 30000) == 0)
    return false;
  if (sendATcommand((char*)"AT+CIPSTATUS\r", (char*)"GPRSACT", 500) == 0)
    return false;
  if (sendATcommand((char*)"AT+CIFSR\r", (char*)".", 10000) == 0)
    return false;
  delay(5000);
  if (sendATcommand((char*)"AT+CIPSTATUS\r", (char*)"IP STATUS", 2000) == 0)
    return false;

  OUT->println(F("GPRS Initialized..."));
  return true;
}

bool SIM8000::startTCP(char *servername, int port)
{
  char str[100];
  memset(str, 0, sizeof(str));
  sprintf((char *)str, "AT+CIPSTART=\"TCP\",\"%s\",\"%d\"", servername, port);
  //str[strlen(str)] = '\0';
  if (sendATcommand(str, (char*)"OK\r\n\r\nCONNECT", 30000) == 0)
    return false;
  OUT->print(F("TCP Connection opened in mode ="));
  OUT->println(this->mode);
  return true;
}

bool SIM8000::closeTCP()
{
  char str[100];
  memset(str, 0, sizeof(str));
  sprintf((char *)str, "AT+CIPSHUT");
  //str[strlen(str)] = '\0';
  if (sendATcommand(str, (char*)"CLOSE OK", 30000) == 0)
    return false;
  OUT->print(F("TCP Connection closed"));
  return true;
}

bool SIM8000::setMode(uint8_t mode)
{
  if (mode == 0)
    if (sendATcommand((char*)"AT+CIPMODE=0\r", (char*)"OK", 1000) == 0)
      return false;
    else if (mode == 1)
      if (sendATcommand((char*)"AT+CIPMODE=1\r",(char*)"OK", 1000) == 0)
        return false;

  this->mode = mode;
  return true;
}

short int SIM8000::getMode()
{
  return mode;
}

bool SIM8000::checkNetwork()
{
  if (sendATcommand((char*)"AT+CREG?\r", (char*)"+CREG: 0,1", 1000) == 0)
    return false;
  return true;
};

bool SIM8000::checkGPRS(){

};

bool SIM8000::getMACAddress()
{
}

bool SIM8000::getIPAddress()
{
}

void SIM8000::resetModem()
{
#ifdef debug
  OUT->println(F("Resetting Modem... please wait for 10 seconds.."));
#endif
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  delay(15000);
};

char *SIM8000::getTCPStatus()
{
  char response[500];
  return sendATCommandResponse((char*)"AT+CIPSTATUS\r", 1000, response);
}

void SIM8000::setAPN(char *APN, char *username, char *password){

};

int8_t SIM8000::sendATcommand(char *ATcommand, char *expected_answer, unsigned int timeout)
{

  uint8_t x = 0, answer = 0;
  char response[300];
  unsigned long previous;
  char *str;
  memset(response, '\0', 100); // Initialize the string
  delay(100);
  while (Serial1.available() > 0)
    Serial1.read();           // Clean the input buffer
  Serial1.println(ATcommand); // Send the AT command

#ifdef debug
  OUT->println(ATcommand); // Send the AT command
#endif
  x = 0;
  previous = millis();
  // this loop waits for the answer
  do
  {
    if (Serial1.available() != 0)
    {
      // if there are data in the Serial1 input buffer, reads it and checks for the asnwer
      response[x] = Serial1.read();
      //Serial1.print(response[x]);
      x++;
      // check if the desired answer  is in the response of the module
      if (strstr(response, expected_answer) != NULL)
      {
        answer = 1;
      }
    }
  }
  // Waits for the asnwer with time out
  while ((answer == 0) && ((millis() - previous) < timeout));
#ifdef debug
  OUT->println(response); // Send the AT command
#endif
  return answer;
}

char *SIM8000::sendATCommandResponse(char *ATcommand, unsigned int timeout, char* response)
{
  unsigned long previous = millis();
  uint8_t index = 0;
  //while (Serial1.available())
  //  Serial1.read();

  OUT->println(ATcommand);
  while (1)
  {
    if ((millis() - previous) > timeout)
      break;
    if (Serial1.available())
    {
      while (Serial1.available())
      {
        response[index] = (char)Serial1.read();
        index++;
      }
      response[index] = '\0';
    }
    if (strlen(response) > 0)
      return response;
    else
      return 0;
  }
  return 0;
}
