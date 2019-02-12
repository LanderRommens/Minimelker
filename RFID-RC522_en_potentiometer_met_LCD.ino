#include <Wire.h>                   // Toevoegen van de bibliotheek Wire
#include <LiquidCrystal_I2C.h>      // Toevoegen van de bibliotheek LiquidCrystal_I2C
#include <SPI.h>                    // Toevoegen van de bibliotheek SPI
#include <MFRC522.h>                // Toevoegen van de bibliotheek MFRC522

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

int potPin = A0;    // Selecteer de ingangspin voor de potentiometer
int val1 = 0;       // Aanmaken variable 'val1', waarde opslaan van sensor, begin variable is 0.
int val2 = 0;       // Aanmaken variable 'val2', waarde opslaan van sensor, begin variable is 0.
int xx = 0;         // Aanmaken variable 'xx', verschil opslaan van val1-val2, begin variable is 0.

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

  lcd.setCursor(0,0);
  lcd.print("Klaar voor scan");       // Drukt de tekst af op het LCD-scherm
  delay(1000);                        // Wacht 1 seconden voor de volgende stap
  //for (int i=0; i<16; i++){            // Maak i=0, zolang i<16 volg deze 'for'-lus, na elke herhaling v.d. lus neemt i met 1 toe
  //lcd.scrollDisplayRight();            // Scrol één positie naar rechts
  //delay(200);}                         // Wacht 0.2 seconden voor de volgende stap
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
}

void loop()
{
  
  val2 = analogRead(potPin);      // Leest de waarde van de opgegeven analoge pin en slaagt deze op bij val2
  delay(1000);                    // Wacht 1 seconden voor de volgende stap
  lcd.setCursor(0, 1);            // Dit normaal met lcd.clearLine(1); maar werkt niet: vraag uitleg 
  lcd.print("                ");  // Dit normaal met lcd.clearLine(1); maar werkt niet: vraag uitleg
  //lcd.clearLine(1)                // Wist de 2de rij van het lcd-scherm
  val1 = analogRead(potPin);      // Leest de waarde van de opgegeven analoge pin en slaagt deze op bij val1
  lcd.setCursor (0,1);            // Volgende tekst die op het LCD-scherm verschijnt begint op de 1ste kolom en de 2de rij
  lcd.print("Pot:");              // Drukt de tekst af op het LCD-scherm
  lcd.setCursor (4,1);            // Volgende tekst die op het LCD-scherm verschijnt begint op de 5de kolom en de 2de rij
  lcd.print(val1);                // Drukt de waarde van 'val1' af op het LCD-scherm
  xx = val1 - val2;               // Stel xx gelijk aan het verschil van val1 en val2
  lcd.setCursor (8,1);            // Volgende tekst die op het LCD-scherm verschijnt begint op de 8ste kolom en de 2de rij
  lcd.print("Vrs:");              // Drukt de tekst af op het LCD-scherm
  lcd.setCursor (12,1);           // Volgende tekst die op het LCD-scherm verschijnt begint op de 13de kolom en de 2de rij
  lcd.print(xx);                  // Drukt de waarde van 'xx' af op het LCD-scherm
    
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
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1) == "A5 E2 55 D3")        // Voor de RFID-tag met A5 E2 55 D3 als code: volg deze lus
  {
    lcd.clear();                  // Wist het lcd-scherm
    lcd.print("Blauw ding");      // Drukt de tekst af op het LCD-scherm
    delay(2000);                  // Wacht 2 seconden voor de volgende stap
       
  }
 
  else   {
        if (content.substring (1) == "FA 48 08 85")       // Voor de RFID-tag met FA 48 08 85 als code: volg deze lus
        {
        lcd.clear();                  // Wist het lcd-scherm
        lcd.print("Witte kaart");     // Drukt de tekst af op het LCD-scherm
        delay(2000);                  // Wacht 2 seconden voor de volgende stap
        }
        else  {
          if (content.substring (1) == "5D 30 C2 21")       // Voor de RFID-tag met 5D 30 C2 21 als code: volg deze lus
          {
          lcd.clear();                      // Wist het lcd-scherm
          lcd.print("Leerlingenkaart");     // Drukt de tekst af op het LCD-scherm
          delay(2000);                      // Wacht 2 seconden voor de volgende stap
          }
          else  {
            if (content.substring (1) == "CD 96 F9 EA")        // Voor de RFID-tag met CD 96 F9 EA als code: volg deze lus
            {
            lcd.clear();                    // Wist het lcd-scherm
            lcd.print("Kaart m. Wyns");      // Drukt de tekst af op het LCD-scherm
            delay(2000);                    // Wacht 2 seconden voor de volgende stap
            }
            else  {                                       // Voor RFID-tags met een andere code als bovenstaande: volg deze lus
              lcd.clear();                                              // Wist het lcd-scherm
              lcd.print("Niet gekend");                                 // Drukt de tekst af op het LCD-scherm
              lcd.setCursor(0, 1);                                      // Volgende tekst begint op de 1ste kolom en de 2de rij
              for (byte i = 0; i < mfrc522.uid.size; i++){
              lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
              lcd.print(mfrc522.uid.uidByte[i], HEX);
              }
              delay(2000);                                              // Wacht 2 seconden voor de volgende stap
            }   //Einde else van "Kaart m. Wyns"
          }     //Einde else van "Leerlingenkaart"
        }       //Einde else van "Witte kaart"
  }             //Einde else van "Blauw ding"
}               //Einde van void loop
