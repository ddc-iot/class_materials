/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"

// Create colors by taking hue angle / 360 as a percentage of 255
const int red = 0;
const int orange = (30.0/360.0)*255;
const int yellow = (60.0/360.0)*255;
const int green = (120.0/360.0)*255;
const int blue = (240.0/360.0)*255;
const int indigo = (260.0/360.0)*255;
const int violet = (270.0/360.0)*255;

const int rainbow[] = {red,orange,yellow,green,blue,indigo,violet};

const int PIXEL_COUNT = 25; 

int i,n,color;
byte returnHue;

Adafruit_NeoPixel pixel(PIXEL_COUNT, SPI1, WS2812B);

uint32_t hueWheel(byte WheelPos);
byte reverseWheel(uint32_t color);

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  pixel.begin();
  pixel.setBrightness(31);
  pixel.show();

  n=0;
}

void loop() {
  color = hueWheel(rainbow[n%7]);
  Serial.printf("Color = %06X\n",color);
  for(i=0;i<PIXEL_COUNT;i++) {
    pixel.setPixelColor(i,color);
  }
  pixel.show();
  returnHue = reverseWheel(color);
  Serial.printf("n = %i: hue = %i: color = %06X: reverse hue = %i\n",n,rainbow[n%7],color,returnHue);
  n++;
  delay(2500);
}

// Convert hue to rgb (hue values 0 - 255 equal 0 to 360 degrees)
uint32_t hueWheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixel.Color(255 - WheelPos * 3, WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixel.Color( 0, 255 - WheelPos * 3, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixel.Color( WheelPos * 3, 0, 255 - WheelPos * 3);
  }
}

// Convert rgb hexcolor to hue
byte reverseWheel(uint32_t color) {
  byte r,g,b;

  r = color>>16 & 0xFF;
  g = color>>8 & 0xFF;
  b = color & 0xFF;

  if(b==0) {
    return (g/3);
  }

  if(g==0) {
    return ((r/3)+170);
  }

  if(r==0) {
    return ((b/3)+85);
  }

  return -1;
}