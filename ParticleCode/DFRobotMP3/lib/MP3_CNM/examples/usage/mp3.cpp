/* 
 * Project MP3 Player Test
 * Author: Brian Rashap
 * Date: 10-APR-2024
 */

/* Wiring Note
 * The MP3 Player is accessed through the Particle's UART pins (SERIAL1)
 * Connect the Tx of the Particle is wired to the Rx of the MP3 player
 * and visa-versoe for the Rx pin.
 * 
 * There is a fritzing diagram of the proper wiring in the class_materials/ParticleCode respository
*/

#include "Particle.h"
#include "DFRobotDFPlayerMini.h"

const int BUTTONPIN=D0;
bool buttonState, prevButtonState;

DFRobotDFPlayerMini myDFPlayer;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {

  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  Serial1.begin(9600);
  delay(1000);

  Serial.printf("DFRobot DFPlayer Mini Demo\n");
  Serial.printf("Initializing DFPlayer ... (May take 3~5 seconds)\n");
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.printf("Unable to begin:\n");
    Serial.printf("1.Please recheck the connection!\n");
    Serial.printf("2.Please insert the SD card!\n");
    while(true);
  }
  Serial.printf("DFPlayer Mini online.\n");
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);     //Play the first track on the uSD card
  
  //The below code should loop each track, may or may not work
  //myDFPlayer.loop(1);
  //myDFPlayer.enableLoopAll();
}

void loop() {
  buttonState = digitalRead(BUTTONPIN);
  if(buttonState != prevButtonState) {
    if(buttonState) {
      Serial.printf("Next Song\n");
      myDFPlayer.next();  /// myDFPlayter.prev() for previous track
    }
  }
  prevButtonState = buttonState;
}