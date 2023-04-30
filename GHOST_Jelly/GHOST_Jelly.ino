#include <Wire.h>
#include <math.h>

// Buoyancy
const float neutral = 14.35;
const float tol = 0.02;

// Pressure sensor globals
const byte sensorAddress = 0x28; // I2C address of the pressure sensor
const int pRegister = 0x00; // register address for the pressure data
const int pBytes = 2; // number of bytes for the pressure data
const float pMax = 15.0; // maximum pressure range of the sensor in psi
const float pMin = 0.0; // minimum pressure range of the sensor in psi
const float oMin = 0.1 * pow(2, 14);
const float oMax = 0.9 * pow(2, 14);

// Stepper motor globals
const int stepperDir = 13;
const int steps = 15;
const int stepsPerRev = 2000;
const int maxRange = 100;
const int minRange = 10;

// Electromagnet globals
const int emDir = 8;
const int PWM_Pin = 7;

void setup()
{
    Wire.begin(); // init I2C comms
    Wire.setClock(20000); // set clock speed to 20 mHz

    pinMode(stepperDir, OUTPUT);
    pinMode(steps, OUTPUT);

    pinMode(emDir, OUTPUT);
    pinMode(PWM_Pin, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    float p = ReadPressure();
    
    while(p < neutral + tol)
    {
        Serial.print("Light 'em up, up, up\n");
        digitalWrite(stepperDir, HIGH);
        
        digitalWrite(steps, HIGH);
        delayMicroseconds(1000);
        digitalWrite(steps, LOW);
        delayMicroseconds(1000);

        p = ReadPressure();
        Serial.print("Pressure (psi): ");
        Serial.println(p);
        delay(36);
    }


    while(p > neutral - tol)
    {
        Serial.print("It's goin down for real\n");
        digitalWrite(stepperDir, LOW);
        
        digitalWrite(steps, HIGH);
        delayMicroseconds(1000);
        digitalWrite(steps, LOW);
        delayMicroseconds(1000);

        p = ReadPressure();
        Serial.print("Pressure (psi): ");
        Serial.println(p);

        delay(36);
    }

    delay(36);
}

float ReadPressure()
{
    // request pressure data from the sensor
    Wire.beginTransmission(sensorAddress);
    Wire.write(pRegister);
    Wire.endTransmission();
    Wire.requestFrom((int)sensorAddress, (int)pBytes);
    
    // read pressure data from the sensor
    int pRaw = (Wire.read() << 8) | Wire.read();
    
    // convert pressure data to a pressure value
    float p = (pRaw - oMin) * (pMax - pMin) / (oMax - oMin) + pMin;

    float pTot = 0;
    float avg = 0;

    // Pressure loop for TEENSY 4.1
    if (p < 16.0)
    {
        for(int x = 0; x < 100; x++)
        {
        pTot += p;
        }
        avg = pTot/100;
    }

    // Pressure loop for Arduino boards
    if (p < 16.0)
    {
        for(int x = 0; x < 100; x++)
        {
        pTot += p;
        }
        avg = pTot/100;
    }
    return avg;
}