#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int XX = 0;
void setup()
{
lcd.begin(16, 2);  // initialize the lcd
lcd.clear();

}
void loop()
{
int val1 = (analogRead(A0)); //read analog pin A0
lcd.setCursor(5, 0);
lcd.print(val1);
delay (1000);
lcd.setCursor(6, 1);
lcd.print("     ");   // dit normaal met lcd.clearLine(1); maar werkt niet: vraag uitleg
int val2 = (analogRead(A0)); //read analog pin A0
XX= val2 - val1;
lcd.setCursor(6, 1);
lcd.print(XX);
delay(0);



}
