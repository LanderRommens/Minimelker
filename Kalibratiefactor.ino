#include "HX711.h"
#define DOUT  3
#define CLK  2
HX711 scale(DOUT, CLK);
float calibration_factor = 330; //-7050 worked for my 440lb max scale setup
void setup() {
  Serial.begin(9600);
  Serial.println("HX711-kalibratieschets");
  Serial.println("Verwijder alle gewicht van schaal");
  Serial.println("Nadat de metingen beginnen, plaatst u bekend gewicht op schaal");
  Serial.println("Druk op + of a om de kalibratiefactor te verhogen");
  Serial.println("Druk op - of op z om de kalibratiefactor te verlagen");
  scale.set_scale();
  scale.tare(); // Stel de schaal opnieuw in op 0
  long zero_factor = scale.read_average(); // Krijg een basislijnwaarde
  Serial.print("Zero factor: "); // Dit kan worden gebruikt om de noodzaak om de weegschaal tarra te verwijderen. Nuttig in projecten op permanente schaal.
  Serial.println(zero_factor);
}
void loop() {
  scale.set_scale(calibration_factor); // Pas deze kalibratiefactor aan
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" kg"); // Verander dit in kg en pas de kalibratiefactor opnieuw aan als u SI-eenheden volgt als een gezonde persoon
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  delay(500);
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}//1.041a

