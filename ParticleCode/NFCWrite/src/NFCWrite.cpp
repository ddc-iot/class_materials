/* 
 * Project: NFCWrite
 * Description: NFC Write Test Code
 * Author: Brian Rashap
 * Date: 30-MAR-2024
 */

#include "Particle.h"
#include <DFRobot_PN532.h>

const int BLOCK_SIZE = 16;
const int PN532_IRQ = 2;
const int INTERRUPT = 1;
const int POLLING = 0;
// The block to be written
int writeBlock;

DFRobot_PN532_IIC  nfc(PN532_IRQ, POLLING);

uint8_t dataWrite[BLOCK_SIZE] = {"Hello World !"};

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.print("Initializing");
  while (!nfc.begin()) {
    Serial.printf(".");
    delay (1000);
  }
  Serial.printf("\nWaiting for a card......\n");

  // set initial write block
  writeBlock = 2;
}
void loop() {
  // For S50 card/tag, block 1-2, 4-6, 8-10, 12-14... 56-58, 60-62 are for user data
  // You can read/write these blocks freely.
  // Use "MifareClassic_ReadAllMemory.ino" to check all the blocks
  if (nfc.scan()) {
    if (nfc.writeData(writeBlock, dataWrite) != 1) {
      Serial.printf("Block %i write failure\n",writeBlock);
    }
    else {
      Serial.printf("Block %i write sucess\n",writeBlock);
      Serial.printf("Data written(string): $s\n",(char *)dataWrite);
      Serial.printf("Data written(HEX): ");
      for (int i = 0; i < BLOCK_SIZE; i++) {
        Serial.printf("%02X ",dataWrite[i]);
      }
      Serial.printf("\n");
    }
  }
  delay(500);
}