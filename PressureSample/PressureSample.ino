#include <Wire.h>
#include <math.h>

/*
  psi -> air = 14.22
  psi -> water @ depth of 7.5 inches = 14.44
  psi -> water @ depth of 3.25 inches = 14.32
*/

const byte sensorAddress = 0x28; // I2C address of the pressure sensor
const int pressureRegister = 0x00; // register address for the pressure data
const int pressureBytes = 2; // number of bytes for the pressure data
const float pressureMax = 15.0; // maximum pressure range of the sensor in psi
const float pressureMin = 0.0; // minimum pressure range of the sensor in psi
const float oMin = 0.1 * pow(2, 14);
const float oMax = 0.9 * pow(2, 14);


void setup() {
  Wire.begin(); // initialize I2C communication
  Wire.setClock(20000);
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  // request pressure data from the sensor
  Wire.beginTransmission(sensorAddress);
  Wire.write(pressureRegister);
  Wire.endTransmission();
  Wire.requestFrom((int)sensorAddress, (int)pressureBytes);
  
  // read pressure data from the sensor
  int pressureRaw = (Wire.read() << 8) | Wire.read();
  
  // convert pressure data to a pressure value
  float presssure = (pressureRaw - oMin) * (pressureMax - pressureMin) / (oMax - oMin) + pressureMin;

  float pTot = 0;
  // print the pressure value to the serial monitor
 if (presssure > 0.0)
 {
    for(int x = 0; x < 100; x++)
    {
      pTot += presssure;
    }
    float avg = pTot/100;
    Serial.println(avg);
 }

delay(36);
  
}
