#ifndef TFTGRAPH_H
#define TFTGRAPH_H

#include "Arduino.h"
#include "Adafruit_GFX.h"

void drawPointDiagram(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color);

void drawLineDiagram(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color);

void drawGauge(Adafruit_GFX &gfx,uint16_t x, uint16_t y, uint8_t r, float value, float min, float max, uint16_t color);

void drawPieChart(Adafruit_GFX &gfx,int x, int y, uint8_t r, float data[], int start, int end, uint16_t colors[], char names[][15]);

void drawBarChart(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], float start, float end, uint16_t color);

#endif