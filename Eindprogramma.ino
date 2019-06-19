#include <Wire.h>                   // Toevoegen van de bibliotheek Wire
#include <LiquidCrystal_I2C.h>      // Toevoegen van de bibliotheek LiquidCrystal_I2C
#include <SPI.h>                    // Toevoegen van de bibliotheek SPI
#include <MFRC522.h>                // Toevoegen van de bibliotheek MFRC522
#include "HX711.h"                  // Toevoegen van de bibliotheek HX711

#define I2C_ADDR    0x3F      // I2C_ADDR wordt gedefinieerd als waarde 0x3F. Vind uw adres met I2C Scanner
#define BACKLIGHT_pin  3      // BACKLIGHT_pin wordt gedefinieerd als waarde 3
#define En_pin  2             // En_pin wordt gedefinieerd als waarde 2
#define Rw_pin  1             // Rw_pin wordt gedefinieerd als waarde 1
#define Rs_pin  0             // Rs_pin wordt gedefinieerd als waarde 0
#define D4_pin  4             // D4_pin wordt gedefinieerd als waarde 4
#define D5_pin  5             // D5_pin wordt gedefinieerd als waarde 5
#define D6_pin  6             // D6_pin wordt gedefinieerd als waarde 6
#define D7_pin  7             // D7_pin wordt gedefinieerd als waarde 7
#define SS_pin  10            // SS_pin wordt gedefinieerd als waarde 10
#define RST_pin 9             // RST_pin wordt gedefinieerd als waarde 9

#define calibration_factor 22000    // calibration_factor wordt gedefinieerd als waarde 22000. Vind uw factor met Kalibratiefactor
#define DOUT 3                      // DOUT wordt gedefinieerd als waarde 3
#define CLK 2                       // CLK wordt gedefinieerd als waarde 2
HX711 scale(DOUT, CLK);

int n = 0;          // Aanmaken variable 'n', om later onderscheid te maken tussen verschillende RFID-tags, begin variable is 0.

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);      
// maak een variable van het type LiquidCrystal_I2C met de naam lcd dat verbinding maakt met het opgegeven adres en pinnen
MFRC522 mfrc522(SS_pin, RST_pin);                                                       
// maak een variable van het type MFRC522 met de naam mfrc522 dat verbinding maakt met de opgegeven pinnen

void setup()
{
  lcd.begin (16,2);                                 // Instellen van LCD-scherm afmetingen. 16 kolommen en 2 rijen.
  lcd.setBacklightPin(BACKLIGHT_pin,POSITIVE);      // Stelt de achtergrondverlichting in (staat toe dat deze wordt ingeschakeld)
  lcd.setBacklight(HIGH);                           // Zet de achtergrondverlichting aan
  lcd.home ();                                      // Plaatst de cursor op de "home" -positie (linkerbovenhoek van het LCD)

  SPI.begin();            // Beginnen SPI bus     //MFRC522-hardware gebruikt SPI-protocol
  mfrc522.PCD_Init();     // Beginnen MFRC522     //Beginnen MFRC522-hardware

  lcd.setCursor(16,0);
  lcd.print("Klaar voor scan");       // Drukt de tekst af op het LCD-scherm
  delay(1000);                        // Wacht 1 seconden voor de volgende stap
  for (int i=0; i<16; i++){           // Maak i=0, zolang i<16 volg deze 'for'-lus, na elke herhaling v.d. lus neemt i met 1 toe
  lcd.scrollDisplayLeft();            // Scrol één positie naar links
  delay(400);}                        // Wacht 0.4 seconden voor de volgende stap
  delay(750);                         // Wacht 0.75 seconden voor de volgende stap
  lcd.clear();                        // Wist het lcd-scherm
  lcd.setCursor (0,1);                // Volgende tekst die op het LCD-scherm verschijnt begint op de 1ste kolom en de 2de rij
  lcd.print("Klaar voor scan");       // Drukt de tekst af op het LCD-scherm
  delay(750);                         // Wacht 0.75 seconden voor de volgende stap
  lcd.clear();                        // Wist het lcd-scherm
  lcd.print("Klaar voor scan");       // Drukt de tekst af op het LCD-scherm

  scale.set_scale (calibration_factor);   // Stel de kalibratiefactor in
  scale.tare ();                          // Reset de schaal naar 0

}

void loop()
{ if ( n == 0){
       lcd.clear();                    // Wist het lcd-scherm
       lcd.print("Klaar voor scan");      // Drukt de tekst af op het LCD-scherm
       
    if ( ! mfrc522.PICC_IsNewCardPresent()) // Zoek naar nieuwe kaarten
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // Selecteer een van de kaarten
  {
    return;
    
  }
  
  //Show UID on LCD
  String content= "";                              // Maak een variable van het type String met de naam content
  //byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1) == "A5 E2 55 D3")        // Voor de RFID-tag met A5 E2 55 D3 als code: volg deze lus
  {
    lcd.clear();                  // Wist het lcd-scherm
    lcd.print("Paula 1415");      // Drukt de tekst af op het LCD-scherm
    delay(2000);                  // Wacht 2 seconden voor de volgende stap
    scale.tare ();                // Reset de schaal nogmaals naar 0
    n = 1;      
  } 
  else   {
        if (content.substring (1) == "FA 48 08 85")       // Voor de RFID-tag met FA 48 08 85 als code: volg deze lus
        {
        lcd.clear();                  // Wist het lcd-scherm
        lcd.print("Bella 1662");     // Drukt de tekst af op het LCD-scherm
        delay(2000);                  // Wacht 2 seconden voor de volgende stap
        scale.tare ();                // Reset de schaal nogmaals naar 0
        n = 2;
        }
        else  {
          if (content.substring (1) == "5D 30 C2 21")       // Voor de RFID-tag met 5D 30 C2 21 als code: volg deze lus
          {
          lcd.clear();                      // Wist het lcd-scherm
          lcd.print("Leerlingenkaart");     // Drukt de tekst af op het LCD-scherm
          delay(2000);                      // Wacht 2 seconden voor de volgende stap
          scale.tare ();                    // Reset de schaal nogmaals naar 0
          n = 3;
          }
          else  {
            if (content.substring (1) == "CD 96 F9 EA")        // Voor de RFID-tag met CD 96 F9 EA als code: volg deze lus
            {
            lcd.clear();                    // Wist het lcd-scherm
            lcd.print("Kaart m. Wyns");     // Drukt de tekst af op het LCD-scherm
            delay(2000);                    // Wacht 2 seconden voor de volgende stap
            scale.tare ();                  // Reset de schaal nogmaals naar 0
            n = 4;
            }
            else  {                                       // Voor RFID-tags met een andere code als bovenstaande: volg deze lus
              lcd.clear();                                              // Wist het lcd-scherm
              lcd.print("NG: ");                                 // Drukt de tekst af op het LCD-scherm, NG staat voor Niet Gekend
              lcd.setCursor(4, 0);                                      // Volgende tekst begint op de 5de kolom en de 1ste rij
              for (byte i = 0; i < mfrc522.uid.size; i++){
              lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
              lcd.print(mfrc522.uid.uidByte[i], HEX);
              }
              delay(2000);                          // Wacht 2 seconden voor de volgende stap
              scale.tare ();                        // Reset de schaal nogmaals naar 0
              n = 5;
            }   //Einde else van "Kaart m. Wyns"
          }     //Einde else van "Leerlingenkaart"
        }       //Einde else van "Witte kaart"
  }             //Einde else van "Blauw ding"  
}               //Einde if ( n == 0)

  else{

    lcd.setCursor (0,1);                  // Volgende tekst die op het LCD-scherm verschijnt begint op de 1ste kolom en de 2de rij
    lcd.print("                ");        // dit normaal met lcd.clearLine(1) maar werkt niet met dit programma
    lcd.setCursor (0,1);                  // Volgende tekst die op het LCD-scherm verschijnt begint op de 1ste kolom en de 2de rij
    lcd.print("Melk:");                   // Drukt de tekst af op het LCD-scherm
    lcd.setCursor (6,1);                  // Volgende tekst die op het LCD-scherm verschijnt begint op de 7de kolom en de 2de rij
    lcd.print (scale.get_units ()/1.03, 1);    // Drukt de waarde van scale.get_units () af op het LCD-scherm
    lcd.setCursor (10,1);                 // Volgende tekst die op het LCD-scherm verschijnt begint op de 11de kolom en de 2de rij
    lcd.print("l");                       // Drukt de tekst af op het LCD-scherm
    delay(1000);                          // Wacht 1 seconde voor de volgende stap
    
  }       //Einde else
}         //Einde van void loop
