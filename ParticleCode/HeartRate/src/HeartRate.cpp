/* 
 * Project HeartRate
 * Description: Sample of using HR monitor with MAX30105
 * Author: Brian Rashap
 * Date: 30-JUN-2035
 */

// NOTES:
// max30105 library can be installed using Particle:Install Libary
// heartRate.h and heartRate.cpp need to be copied from here to your project
 
#include "Particle.h"
#include "max30105.h"
#include "heartRate.h"

MAX30105 theSensor;
int IRvalue, BPM, BPMsum;
unsigned int deltaTime, lastBeat;
bool status;
int count;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,5000);
  delay(500);

  status = theSensor.begin();
  if (status) {
    Serial.printf("The Sensor has started \n");
  }
  else {
    Serial.printf("Danger Will Robinson\n");
  }
  theSensor.setup(); //Configure sensor with default settings
  theSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  theSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  IRvalue = theSensor.getIR();

  if((checkForBeat(IRvalue)) and (IRvalue > 1200)) {
    deltaTime = millis() - lastBeat;
    lastBeat = millis();
    BPM = 60 / (deltaTime/1000.0);
    BPMsum = BPMsum + BPM;
    Serial.printf("IR = %i, BPM = %i\n",IRvalue,BPM);
    count++;
  }

  if(count == 10) {
    Serial.printf("\n****** PULSE ******\n");
    Serial.printf("Average BPM = %i\n",BPMsum/10);
    Serial.printf("****** PULSE ******\n\n");
    count = 0;
    BPMsum = 0;
  }
}
