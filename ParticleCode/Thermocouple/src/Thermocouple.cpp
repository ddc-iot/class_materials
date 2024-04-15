/* 
 * Project Thermocouple using MAX6675
 * Author: Brian Rashap
 * Date: 10-APR-2024
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "MAX6675.h"

MAX6675 thermocouple;
int status;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup () {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  thermocouple.begin(SCK, SS, MISO);
}


void loop () {
  status = thermocouple.read();
  if (status != STATUS_OK) {
    Serial.printf("ERROR!\n");
  }

 // Read the raw Data value from the module
  Serial.printf("RAW: 0x%08X\n",thermocouple.getRawData());

  Serial.printf("TMP: %0.3f\n",thermocouple.getTemperature());
  delay(500);
}