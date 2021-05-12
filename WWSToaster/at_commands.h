// #include <SoftwareSerial.h>

// const int SIM_RX_PIN = 7;
// const int SIM_TX_PIN = 8;

// // SoftwareSerial mySerial(SIM_TX_PIN, SIM_RX_PIN);

// // void testingAtCommands()
// // {
// //     //Begin serial communication with Arduino and SIM800L
// //     mySerial.begin(9600);

// //     Serial.println("Initializing...");
// //     delay(1000);

// //     mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
// //     updateSerial();
// //     mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
// //     updateSerial();
// //     mySerial.println("AT+CMEE=2");
// //     updateSerial();
// //     delay(5000);
// //     mySerial.println("AT+CREG=0");
// //     updateSerial();
// //     mySerial.println("AT+CREG=1");
// //     updateSerial();
// //     mySerial.println("AT+CREG=2");
// //     updateSerial();
// //     updateSerial();
// //     mySerial.println("AT+COPS=?");
// //     updateSerial();
// //     delay(15000);
// //     mySerial.println("AT+COPS?");
// //     updateSerial();

// //     delay(15000);
// //     // mySerial.println("AT+COPS=1,0,\"22210\"");
// //     // updateSerial();
// //     // delay(10000);
// //     // mySerial.println("AT+COPS=2");
// //     // updateSerial();
// //     // delay(10000);
// //     mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
// //     updateSerial();
// //     // mySerial.println("AT+CFUN = 0");
// //     // updateSerial();
// //     // delay(5000);
// //     // mySerial.println("AT+CFUN = 1");
// //     // updateSerial();
// //     delay(1000);
// //     mySerial.println("AT+CGREG?"); //Check whether it has registered in the network
// //     updateSerial();
// //     mySerial.println("AT+CBC");
// //     updateSerial();
// //     delay(1000);
// //     mySerial.println("AT+CSTT=\"mobile.vodafone.it\",\"\",\"\"");
// //     updateSerial();
// //     delay(1000);
// //     mySerial.println("AT+CIICR");
// //     updateSerial();
// //     delay(1000);
// //     mySerial.println("AT+CIFSR");
// //     updateSerial();
// //     delay(5000);
// //     // mySerial.println("AT+CIPSTART=\"TCP\",\"93.63.173.7\",\"1883\"");
// //     mySerial.println("AT+CIPSTART=\"TCP\",\"test.mosquitto.org\",\"1883\"");
// //     updateSerial();
// //     delay(3000);
// //     mySerial.println("AT+CIPSEND");
// //     updateSerial();

// //     // mySerial.println("AT+CMGF=1\r");
// //     // mySerial.println("AT+CMGS=\"+39xxxxxxxxxx\"\r");
// //     // updateSerial();
// //     delay(1000);
// //     mySerial.write("Ciao sono WWS Toaster, l'Arduino di Auriga S.p.A.");
// //     delay(500);
// //     mySerial.write((char)26);
// //     delay(500);
// //     mySerial.println("AT+CIPCLOSE");
// //     updateSerial();
// // }

// void updateSerial()
// {
//   delay(500);
//   while (Serial.available())
//   {
//     mySerial.write(Serial.read()); //Forward what Serial received to Software Serial Port
//   }
//   while (mySerial.available())
//   {
//     Serial.write(mySerial.read()); //Forward what Software Serial received to Serial Port
//   }
// }