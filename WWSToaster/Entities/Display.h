// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
byte topLeftLogo[] = {
    B00000,
    B01110,
    B10001,
    B10000,
    B10000,
    B01000,
    B01000,
    B00100};

byte topRightLogo[] = {
    B00000,
    B00000,
    B00000,
    B10000,
    B01000,
    B00000,
    B00000,
    B00000};

byte bottomLeftLogo[] = {
    B00010,
    B00010,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
    B00000};

byte bottomRightLogo[] = {
    B00000,
    B00000,
    B01000,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000};

class Display
{

public:
  void setup()
  {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print(F("Vassallo is "));
    lcd.setCursor(0, 1);
    lcd.print(F("starting..."));
  }

  void started()
  {
    lcd.begin(16, 2);
    lcd.createChar(0, topLeftLogo);
    lcd.createChar(1, topRightLogo);
    lcd.createChar(2, bottomLeftLogo);
    lcd.createChar(3, bottomRightLogo);
    lcd.setCursor(0, 0);
    lcd.print(F(" "));
    // Print a message to the LCD.
    lcd.write(byte(0));
    lcd.write(byte(1));
    lcd.print(F("Auriga S.p.A."));
    lcd.setCursor(1, 1);
    lcd.write(byte(2));
    lcd.write(byte(3));
  }

  void turnOn()
  {
    digitalWrite(RELAY_PIN, LOW);
  }

  void turnOff()
  {
    digitalWrite(RELAY_PIN, HIGH);
  }
};
