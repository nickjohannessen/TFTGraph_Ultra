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

void setup() {
  tft.begin(0x9325);

  tft.reset();
  tft.fillScreen(0x0000);
}

void loop() {
  tft.setRotation(1);

  tft.fillScreen(BLACK);

  gfx.drawGauge(320/2, 150, 128, 145, -400, 360, 0xF456);

  delay(1000);
}