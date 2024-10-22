/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_BME280.h"

Adafruit_BME280 bme;

bool status;
int sensorType;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  delay(2000);

  bme.begin(0x76);
  sensorType = bme.sensorID();
  Serial.printf("Sensor ID is: 0x%02X\n",sensorType);

  Serial.printf("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
  Serial.printf("   ID of 0x56-0x58 represents a BMP 280,\n");
  Serial.printf("        ID of 0x60 represents a BME 280.\n");
  Serial.printf("        ID of 0x61 represents a BME 680.\n\n\n");

  switch(sensorType) {
    case 0x56:
      Serial.printf("Hmm, someone switched out your BME with a BMP280\n");
      break;
    case 0x57:
      Serial.printf("Hmm, someone switched out your BME with a BMP280\n");
      break;
    case 0x58:
      Serial.printf("Hmm, someone switched out your BME with a BMP280\n");
      break;
    case 0x60:
      Serial.printf("Congratulations, you have a BME280!!!!!\n");
      break;
    case 0x61:
      Serial.printf("Only the most special students get a BME680\n");
      break;
    case 0xFF:
      Serial.printf("Something is wrong, possibly your wires or the soldering\n");
      break;
    default:
      Serial.printf("Unfortunately, I am confused with what you put on your board\n");
      break;
  }

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {}
