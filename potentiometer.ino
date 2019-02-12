int potPin = 2;    // select the input pin for the potentiometer
int val1 = 0;       // variable to store the value coming from the sensor
int val2 = 0;
int xx = 0;


void setup() {

  Serial.begin(9600);
  Serial.println("Ja nu zen ik kleir");
  Serial.println(" ********************************");
}

void loop() {
  val2 = analogRead(potPin);    // read the value from the sensor
  delay(1000);
  val1 = analogRead(potPin);    // read the value from the sensor
  Serial.print("Potwaarde : ");
  Serial.println(val1);
  Serial.println("");
  xx = val1 - val2;
  Serial.print("Verschil : ");
  Serial.println(xx);
  Serial.println(" -------------------------");
}

 
