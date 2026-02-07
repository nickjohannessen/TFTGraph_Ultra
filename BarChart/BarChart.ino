#include <math.h>
#include <Adafruit_TFTLCD.h>
#include <TFTGraph.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD gfx;
TFTGraph tft(gfx);

void setup() {
  gfx.begin(0x9325);
  gfx.reset();
  gfx.setRotation(1);

  gfx.fillScreen(BLACK);
}

void loop() {
  gfx.fillScreen(BLACK);
  float data[] = {5,10,20,10,67,65,32,54};
  tft.drawBarChart(40, 15, 270, 190, data, 0,sizeof(data)/sizeof(data[0]), 0xFF45);
  delay(10000);
}