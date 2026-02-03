#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD tft;

void setup(){
  tft.begin(0x9325);
  tft.reset();

  tft.fillScreen(BLACK);
}

void loop(){
  float data[] = {5,45,4,1,6,100,160,43,58};
  int dataSize = sizeof(data) / sizeof(data[0]);
  uint16_t colors[] = {0xf800, 0xfca0, 0xefe0, 0x5fe0, 0x07fe, 0x201f, 0xf81f};
  drawPieChart(160, 100, 64, data, 0, dataSize, colors);

  delay(100000);
}

void drawPieChart(int x, int y, uint8_t r, float data[], int start, int end, uint16_t colors[]) {
  //sum all values as well as getting minimum and maximum values:
  float sum = 0.0;
  float min = data[0];
  float max = data[0];
  for(int i = start; i < end; i++){
    sum += data[i];

    if(data[i] < min){
      min = data[i];
    }else if(data[i] > max){
      max = data[i];
    }
  }
  
  float currentAngle = 0.0;

  for(int i = start; i<end; i++){
    float angleAdd = 360.0 * (data[i] / sum);

    tft.drawLine(x,y,
    x+cosd(currentAngle)*r, y+sind(currentAngle)*r,
    colors[i]);

    //drawing colours on top:
    //A LOT OF THIS IS CHATGPT CODE, NEEDS SOME MAJOR REFACTORING:
    for(uint16_t i2 = 0; i2 < r*2; i2++){
  for(uint16_t i3 = 0; i3 < r*2; i3++){
    float dx = ((x - r) + i2) - x;
    float dy = ((y - r) + i3) - y;

    float dist = sqrt(dx*dx + dy*dy);
    if(dist > r) continue; // skip pixels outside the circle

    float anglePixel = atan2(dy, dx) * 180.0 / PI; // convert to degrees
    if(anglePixel < 0) anglePixel += 360;

    float startAngle = fmod(currentAngle, 360.0);
    float endAngle = fmod(currentAngle + angleAdd, 360.0);
    if(startAngle < 0) startAngle += 360;
    if(endAngle < 0) endAngle += 360;

    bool isBetween;
    if(startAngle < endAngle){
        isBetween = (anglePixel >= startAngle && anglePixel <= endAngle);
    } else {
        isBetween = (anglePixel >= startAngle || anglePixel <= endAngle);
    }

    if(isBetween){
        tft.drawPixel((x - r) + i2, (y - r) + i3, colors[i]);
    }else{
      continue;
    }
  }
}
currentAngle += angleAdd;
  }

  //draw bounding circle:
  //tft.drawCircle(x,y,r,WHITE);
}

//Helper functions:
static double sind(double deg) {
    return sin(deg * M_PI / 180.0);
}

static double cosd(double deg) {
    return cos(deg * M_PI / 180.0);
}
