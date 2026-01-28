#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD tft;

void setup() {
  tft.begin(0x9325);

  tft.reset();
  tft.fillScreen(0x0000);
}

void loop() {
  tft.setRotation(1);

  tft.fillScreen(BLACK);

  drawGaugeChart(320/2, 150, 128, 145, -400, 360, 0xF456);

  delay(10000);
}

//This needs more memory optimization. After stress-testing it seems to be able to handle ~400 data values in the array.
void drawGaugeChart(uint16_t x, uint16_t y, uint8_t r, float value, float min, float max, uint16_t color){
  drawHalfCircle(x,y,r,WHITE);

  float step = (max - min) / 8;
  float currentStep = min;

  //draw base of arrow (simple point):
  tft.drawFastHLine(x-1,y,3,WHITE);
  tft.drawFastVLine(x,y-1,3,WHITE);

  //Drawing gauge line:
  int Ang = 260 + ((value - min) * (100 - 260)) / (max - min);
  tft.drawLine(
    x,
    y,
    x+sind(Ang)*(r-(r/5)),
    y+cosd(Ang)*(r-(r/5)),
    color);

  //draw text:
  for(int i = 26; i>9; i--){

    bool offset = false;
    if(i<=16){
      offset = true;
    }

    if(i % 2 == 0){
      tft.setCursor(
        x+sind(i*10)*(r-5)+((String(currentStep).length()*2)*(offset*-1)),
        y+cosd(i*10)*(r-5));
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      tft.print(currentStep,0);
      currentStep += step;
    }
  }

  //Draw arrow:
  //tft.drawPixel(x,y+cos(90));
}

//This function uses the "midpoint" algorithm, basically just draw 1/8th of the circle and mirror it (and skip drawing half the circle in this case.):
void drawHalfCircle(uint16_t xc, uint16_t yc, uint8_t r, uint16_t color) {
    int16_t x = 0;
    int16_t y = r;
    int16_t p = 1 - r;

    while (x <= y) {
        if(yc + y <= yc) tft.drawPixel(xc + x, yc + y, color);
        if(yc + y <= yc) tft.drawPixel(xc - x, yc + y, color);
        if(yc - y <= yc) tft.drawPixel(xc + x, yc - y, color);
        if(yc - y <= yc) tft.drawPixel(xc - x, yc - y, color);
        if(yc + x <= yc) tft.drawPixel(xc + y, yc + x, color);
        if(yc + x <= yc) tft.drawPixel(xc - y, yc + x, color);
        if(yc - x <= yc) tft.drawPixel(xc + y, yc - x, color);
        if(yc - x <= yc) tft.drawPixel(xc - y, yc - x, color);

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

//Helper functions:
double sind(double deg) {
    return sin(deg * M_PI / 180.0);
}

double cosd(double deg) {
    return cos(deg * M_PI / 180.0);
}