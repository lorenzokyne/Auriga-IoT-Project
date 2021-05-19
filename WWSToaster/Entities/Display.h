// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
byte aurigaLogo1[] = {
    B01110,
    B11011,
    B10000,
    B10000,
    B11000,
    B01100,
    B00110,
    B00011};

byte aurigaLogo2[] = {
    B00000,
    B00000,
    B10000,
    B00000,
    B00000,
    B00000,
    B01100,
    B11000};

class Display
{

public:
    void setup()
    {
        lcd.begin(16, 2);
        lcd.setCursor(0, 0);
        // Print a message to the LCD.
        lcd.print("Vassallo is ");
        lcd.setCursor(0, 1);
        lcd.print("starting");
    }

    void started()
    {
        lcd.begin(16, 2);
        lcd.createChar(0, aurigaLogo1);
        lcd.createChar(1, aurigaLogo2);
        lcd.setCursor(0, 0);
        lcd.print(" ");
        // Print a message to the LCD.
        lcd.write(byte(0));
        lcd.write(byte(1));
        lcd.print("Auriga S.p.A");
    }
};
