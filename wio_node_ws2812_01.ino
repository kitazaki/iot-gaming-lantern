#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN 5   // Grove Port 1 IO4 or IO5
#define NUMPIXELS 16   // Number of LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void led(int v_s) {
  strip.setBrightness(v_s);
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(255,255,255));
    strip.show();
    delay(10);
  }
}

void led_wipe_a(int v_r, int v_g, int v_b, int v_s) {
  strip.setBrightness(v_s);
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(v_r,v_g,v_b));
    strip.show();
    delay(50);
  }
  for(int i=0;i<NUMPIXELS;i++){
//    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.setPixelColor(NUMPIXELS - i - 1, strip.Color(0,0,0));
    strip.show();
    delay(50);
  }
}

void led_wipe_b(int v_r, int v_g, int v_b, int v_s) {
  strip.setBrightness(v_s);
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(v_r,v_g,v_b));
    strip.show();
    delay(50);
  }
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(0,0,0));
//    strip.setPixelColor(NUMPIXELS - i - 1, strip.Color(0,0,0));
    strip.show();
    delay(50);
  }
}

void rainbow(int v_s, uint8_t wait) {
  uint16_t i, j;
  strip.setBrightness(v_s);
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(int v_s, uint8_t wait) {
  uint16_t i, j;
  strip.setBrightness(v_s);
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, int v_s, uint8_t wait) {
  strip.setBrightness(v_s);
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int v_s, uint8_t wait) {
  strip.setBrightness(v_s);
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// main
void setup() {
  pinMode(15, OUTPUT);
  digitalWrite(15, 1);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
  delay(10);
  led(20);
}

void loop() {
  rainbow(20, 10);
//  rainbowCycle(20, 0);
//  delay(100);
}
