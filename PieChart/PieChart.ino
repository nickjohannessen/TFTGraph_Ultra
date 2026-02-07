#include <math.h>
#include <Adafruit_TFTLCD.h>
#include <TFTGraph.h>

#define BLACK 0x0000

Adafruit_TFTLCD tft;
TFTGraph gfx(tft);

void setup(){
  tft.begin(0x9325);
  tft.reset();
  tft.setRotation(1);

  tft.fillScreen(BLACK);
}

void loop(){
  tft.fillScreen(BLACK);
  float data[] = {5,45,4,1,6,67};
  int dataSize = sizeof(data) / sizeof(data[0]);
  uint16_t colors[] = {0xf800, 0xfca0, 0xefe0, 0x5fe0, 0x07fe, 0x201f, 0x0393, 0x9800, 0xf800};
  char names[][15] = {
    "test1",
    "test2",
    "test3",
    "test4",
    "test5",
    "test6"
  };

  gfx.drawPieChart(120, 100, 48, data, 0, dataSize, colors, names);
  //can also do this:
  //TFTGraph::drawPieChart(tft,120, 100, 128, data, 0, dataSize, colors, names);
  delay(10000);
}