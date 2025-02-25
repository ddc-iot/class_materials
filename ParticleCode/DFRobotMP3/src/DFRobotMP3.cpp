/* 
 * Project MP3 Player Test
 * Author: Brian Rashap
 * Date: 10-APR-2024
 */

#include "Particle.h"
#include "DFRobotDFPlayerMini.h"
#include "Button.h"

DFRobotDFPlayerMini myDFPlayer;
Button nextButton(D0);
unsigned int lastSong;
void printDetail(uint8_t type, int value);

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
  myDFPlayer.loop(1);  //Play the first mp3
  myDFPlayer.enableLoopAll();
}

void loop() {
  if(nextButton.isClicked()) {
    Serial.printf("Next Song\n");
    myDFPlayer.next(); 
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.printf("Time Out!\n");
      break;
    case WrongStack:
      Serial.printf("Stack Wrong!\n");
      break;
    case DFPlayerCardInserted:
      Serial.printf("Card Inserted!\n");
      break;
    case DFPlayerCardRemoved:
      Serial.printf("Card Removed!\n");
      break;
    case DFPlayerCardOnline:
      Serial.printf("Card Online!\n");
      break;
    case DFPlayerPlayFinished:
      Serial.printf("Number %i Play Finished!\n",value);
      break;
    case DFPlayerError:
      Serial.printf("DFPlayerError:\n");
      switch (value) {
        case Busy:
          Serial.printf("Card not found\n");
          break;
        case Sleeping:
          Serial.printf("Sleeping\n");
          break;
        case SerialWrongStack:
          Serial.printf("Get Wrong Stack\n");
          break;
        case CheckSumNotMatch:
          Serial.printf("Check Sum Not Match\n");
          break;
        case FileIndexOut:
          Serial.printf("File Index Out of Bound\n");
          break;
        case FileMismatch:
          Serial.printf("Cannot Find File\n");
          break;
        case Advertise:
          Serial.printf("In Advertise\n");
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
