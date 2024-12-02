/*
 * Project PECMAC125A
 * Description: NCD Current Monitor
 * Author: Brian Rashap
 * Date:  22-APR-2020
 */

#include "Particle.h"

const int Addr=0x2A; // PECMAC125A I2C address is 0x2A(42)

byte data[36];
int typeOfSensor;
int maxCurrent;
int noOfChannel;
float current;
byte msb1, msb, lsb;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  // Initialise I2C communication as MASTER

  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);

  Wire.begin();
  Wire.beginTransmission(Addr);

  Wire.write(0x92);   // Command header byte-1
  Wire.write(0x6A);  // Command header byte-2
  Wire.write(0x02);  // Command 2 is used to read no of sensor type, Max current, No. of channel
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0xFE);
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);
  if (Wire.available() == 6) {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }
  typeOfSensor = data[0];
  maxCurrent = data[1];
  noOfChannel = data[2];

  Serial.printf("Type of Sensor %i \n",typeOfSensor);
  Serial.printf("Max Current: %i \n", maxCurrent);
  Serial.printf("No. of Channels: %i 'n", noOfChannel);
  delay(5000);
}

void loop() {
  for (int j = 1; j < noOfChannel + 1; j++) {
    Wire.beginTransmission(Addr);
    Wire.write(0x92);    // Command header byte-1
    Wire.write(0x6A);   // Command header byte-2
    Wire.write(0x01);    // Command 1
    Wire.write(j);    // Start Channel No.
    Wire.write(j);    // End Channel No.
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write((0x92 + 0x6A + 0x01 + j + j + 0x00 + 0x00) & 0xFF);     // CheckSum
    Wire.endTransmission();
    delay(500);

    // Request 3 bytes of data
    Wire.requestFrom(Addr, 3);
    int msb1 = Wire.read();
    int msb = Wire.read();
    int lsb = Wire.read();
    current = (msb1 < 16) | (msb < 8) | lsb;

    // Convert the data to ampere
    current = current / 1000;

    // Output data to dashboard
    Serial.printf("Channel: %i \n", j);
    Serial.printf("Current Value: %0.2f \n", current); 
  }
}