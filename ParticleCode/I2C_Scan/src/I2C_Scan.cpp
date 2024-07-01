/*
 * Project I2C_Scan
 * Description: Scan I2C bus and return found addresses
 * Author: Brian Rashap
 * Date: 13-Jan-2020
 */

#include "Particle.h"

byte status; 
byte address;
int nDevices;
unsigned long delayTime=5000;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
	Wire.begin();
	Serial.begin(9600);
	waitFor(Serial.isConnected,10000);
	Serial.printf("I2C Scanner\n");
}

void loop() {
	Serial.printf("Starting Scan: \n-------------- \n");
	nDevices = 0;
	for(address = 1; address < 127; address++ ) {
		Wire.beginTransmission(address);
		status = Wire.endTransmission();
		if (status == 0) {
			Serial.printf("I2C device found at address 0x%02x \n",address);
			nDevices++;
		}
	}
	Serial.printf("%i I2C devices found\n",nDevices);
	Serial.printf("-------------- \nScan Complete!\n");
	delay(delayTime);           // wait 5 seconds for next scan
}