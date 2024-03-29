/* 
 * Project HeyHeyNoDelay
 * Description: starter code for avoiding delays code-along
 * Author: Reed Searle and Brian Rashap
 * Date: 28-MAR-2024
 */

#include "Particle.h"
#include "neopixel.h"
#include "Colors.h"

// Create Pixel Object
const int PIXELCOUNT = 16;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);

// Declare Variables
int color;

// Declare Functions
void pixelFill(int start, int end, int color);

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pixel.begin();
  pixel.setBrightness(31);
  pixel.show();
}

void loop() {
  // the naughty way - using delays
  pixelFill(0,PIXELCOUNT,blue);
  delay(1000);
  pixel.clear();
  pixel.show();
  delay(1000);
}

// Fill pixels from start to end with a color
void pixelFill(int start, int end, int color) {
  int i;
  for(i=start;i<=end;i++) {
    pixel.setPixelColor(i,color);
  }
  pixel.show();
}
