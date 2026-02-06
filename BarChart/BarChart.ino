#include <math.h>
#include <Adafruit_TFTLCD.h>
#include <TFTGraph.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD tft;

void setup() {
  tft.begin(0x9325);
  tft.reset();
  tft.setRotation(1);

  tft.fillScreen(BLACK);
}

void loop() {
  tft.fillScreen(BLACK);
  float data[] = {5,10,20,10,67,65,32,54};
  drawBarChart(tft,25, 15, 200, 200, data, 0,sizeof(data)/sizeof(data[0]), 0xFF45);
  delay(10000);
}