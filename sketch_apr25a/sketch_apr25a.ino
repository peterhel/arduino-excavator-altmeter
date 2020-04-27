int offset = 102; // zero pressure calibrate
int fullScale = 922; // max pressure calibrate
float pressure; // final pressure

int analogPin = A0;
//int val = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
//  val = analogRead(analogPin);
//  Serial.print("Well");
//  Serial.println(val);

  pressure = (analogRead(A0) - offset) * 6.89476  / (fullScale - offset); // pressure conversion
  Serial.print("Pressure is  ");
  Serial.print(pressure);
  Serial.println("  bar");
  delay(500);
}


//Sensor output --> ~5k --> 1µF (ceramic or film) capacitor to ground --> ~500 --> nano input.

//The 5k & 1µF filter the signal, the 500 is to protect the nano in case the power supply is suddenly shorted to ground.

//Add a 0.1µF on the power going to the sensor (near the nano).
