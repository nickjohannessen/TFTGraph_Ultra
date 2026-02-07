#ifndef TFTUTILS_H
#define TFTUTILS_H

#include "Arduino.h"

class InternalUtils {
    public:
        static double sind(double deg);
        static double cosd(double deg);

        static void drawDiagramBody(Adafruit_TFTLCD &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max);

        static void drawHalfCircle(Adafruit_TFTLCD &gfx, uint16_t xc, uint16_t yc, uint8_t r, uint16_t color);
};

#endif