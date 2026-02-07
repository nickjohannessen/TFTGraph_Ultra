#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TFTGraph.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD tft;
TFTGraph gfx(tft);

void fillRandomFloatArray(float arr[], uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    arr[i] = sin(i/10.0)*50;
  }
}

void setup() {
  tft.begin(0x9325);

  tft.reset();
  tft.fillScreen(0x0000);
}

void loop() {
  float data[350];
  fillRandomFloatArray(data, 350);

  tft.setRotation(1);

  tft.fillScreen(BLACK);

  gfx.drawPointDiagram(50, 20, 225, 125, data, 0, 350, -50, 50, 0xF456);

  delay(5000);
}