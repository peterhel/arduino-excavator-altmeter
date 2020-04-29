#include "./Adafruit_MPL3115A2.h"
#include <Wire.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

int offset = 102; // zero pressure calibrate
int fullScale = 922; // max pressure calibrate
float pressure; // final pressure

int analogPin = A0;
int val = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
 
  float pascals = baro.getPressure();
  // Our weather page presents pressure in Inches (Hg)
  // Use http://www.onlineconversion.com/pressure.htm for other units
  Serial.print(pascals/3377); Serial.println(" Inches (Hg)");
 
  float altm = baro.getAltitude();
  Serial.print(altm); Serial.println(" meters");
 
  float tempC = baro.getTemperature();
  Serial.print(tempC); Serial.println("*C");
   delay(250);
}


//Sensor output --> ~5k --> 1µF (ceramic or film) capacitor to ground --> ~500 --> nano input.

//The 5k & 1µF filter the signal, the 500 is to protect the nano in case the power supply is suddenly shorted to ground.

//Add a 0.1µF on the power going to the sensor (near the nano).
