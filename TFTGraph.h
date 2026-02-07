/*
    "TFTGraph"
    Made by Fahim Rouhani, Hedvig Stordalen and Nicolai Wissler
    For bachelor of Spring 2026.

    Released into the public domain.
*/

#ifndef TFTGRAPH_H
#define TFTGRAPH_H

#include "Arduino.h"
#include "Adafruit_TFTLCD.h"

class TFTGraph {
    public:
        TFTGraph(Adafruit_TFTLCD &gfx) : _gfx(gfx) {};

        void drawPointDiagram(int x, int y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color);

        void drawLineDiagram(int x, int y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color);

        void drawGauge(int x, int y, uint8_t r, float value, float min, float max, uint16_t color);

        void drawPieChart(int x, int y, uint8_t r, float data[], int start, int end, uint16_t colors[], char names[][15]);

        void drawBarChart(int x, int y, uint16_t width, uint16_t height, float data[], float start, float end, uint16_t color);

    private:
        Adafruit_TFTLCD &_gfx;
};

#endif