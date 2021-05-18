// #include <SoftwareSerial.h>
// #include <TinyGPS.h>

// int soundAnalogValue = 0;
// int linearHallValue = 0;
// float analogValue;
// float digitalValue;

// // SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
// // TinyGPS gps;
// float lat = 0, lon = 0; // create variable for latitude and longitude


// // void gpsCall()
// // {

// //     Serial.println("Searching GPS signal...");
// //     while (gpsSerial.available())
// //     {
// //         Serial.print("READ: " + gpsSerial.read()); // check for gps data
// //         if (gps.encode(gpsSerial.read()))          // encode gps data
// //         {
// //             gps.f_get_position(&lat, &lon); // get latitude and longitude
// //             // display position

// //             Serial.println("Position: ");
// //             Serial.print("Latitude:");
// //             Serial.print(lat, 6);
// //             Serial.print(";");
// //             Serial.print("Longitude:");
// //             Serial.println(lon, 6);

// //             Serial.print(lat);
// //             Serial.print(" ");
// //         }
// //         String latitude = String(lat, 6);
// //         String longitude = String(lon, 6);
// //         Serial.println(latitude + ";" + longitude);
// //         delay(1000);
// //     }
// //     delay(500);
// // }

// void switchRelayOn()
// {
//     digitalWrite(RELAY_PIN, HIGH);
// }

// void switchRelayOff()
// {
//     digitalWrite(RELAY_PIN, LOW);
// }
