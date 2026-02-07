#include "TFTGraph.h"
#include "InternalUtils.h"
#include "math.h"

double InternalUtils::sind(double deg) {
    return sin(deg * M_PI / 180.0);
}

double InternalUtils::cosd(double deg) {
    return cos(deg * M_PI / 180.0);
}

void InternalUtils::drawDiagramBody(Adafruit_TFTLCD &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max){

    for (uint8_t i = 0; ; i++) {
        int yPos = y + i * 15;
        if (yPos > y + height) break;

        gfx.drawFastHLine(x, yPos, width, 0x8410);

        float t = (float)(yPos - y) / height;
        float value = max - t * (max - min);

	    if ((y + height) - (y+(i * 15)) < 10) break;

        String str = String(value, 1);
        gfx.setCursor((x - 3) - (6 * str.length()), yPos - 4);
        gfx.setTextColor(0xFFFF);
        gfx.setTextSize(1);
        gfx.print(value, 1);
    }

    gfx.drawFastHLine(x, y + height, width, 0x8410);
    gfx.setCursor(x - 3 - 6 * String(min,1).length(), y + height - 4);
    gfx.print(min, 1);

    //drawing bounding box:
    gfx.drawRect(x,y,width+2,height,0xFFFF);
}

void InternalUtils::drawHalfCircle(Adafruit_TFTLCD &gfx, uint16_t xc, uint16_t yc, uint8_t r, uint16_t color){

    int16_t x = 0;
    int16_t y = r;
    int16_t p = 1 - r;

    while (x <= y) {
        if(yc + y <= yc) gfx.drawPixel(xc + x, yc + y, color);
        if(yc + y <= yc) gfx.drawPixel(xc - x, yc + y, color);
        if(yc - y <= yc) gfx.drawPixel(xc + x, yc - y, color);
        if(yc - y <= yc) gfx.drawPixel(xc - x, yc - y, color);
        if(yc + x <= yc) gfx.drawPixel(xc + y, yc + x, color);
        if(yc + x <= yc) gfx.drawPixel(xc - y, yc + x, color);
        if(yc - x <= yc) gfx.drawPixel(xc + y, yc - x, color);
        if(yc - x <= yc) gfx.drawPixel(xc - y, yc - x, color);

        x++;
        if (p < 0) {
            //Midpoint is inside circle
            p = p + 2 * x + 1;
        } else {
            //Midpoint is outside circle
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }
}