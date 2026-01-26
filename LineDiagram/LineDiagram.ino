#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGRAY 0xC618
#define GRAY 0x8410
#define DARKGRAY 0x4208

Adafruit_TFTLCD tft;

void fillRandomFloatArray(float arr[], uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    arr[i] = sin(i/10.0)*50;
  }
}

void setup() {
  tft.begin(0x9325);

  tft.reset();
  tft.fillScreen(0x0000);
}

void loop() {
  float data[100];
  fillRandomFloatArray(data, 100);

  tft.setRotation(1);

  tft.fillScreen(BLACK);

  drawLineDiagram(50, 20, 225, 125, data, 0, 100, -50, 50, 0xF456);

  delay(5000);
}

//This needs more memory optimization. After stress-testing it seems to be able to handle ~400 data values in the array.
void drawLineDiagram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color){

  //"Cleaning" some values:
  x = max(0,x);
  y = max(0,y);
  width = max(5,width);
  height = max(5,height);
  start = min(start, end);
  min = min(min, max);

  /*tft.drawFastVLine(x-2,y-2,height+6,WHITE);
  tft.drawFastVLine(x-3,y-2,height+6,WHITE);*/

  /*
  //retrieving the highest and lowest number in the array:
  float max_num = data[start];
  float min_num = data[start];
  for(uint16_t i = start; i<end; i++){
    if(max_num < data[i]){
      max_num = data[i];
      continue;
    } else if(min_num > data[i]){
      min_num = data[i];
    }else{
      continue;
    }
  }
  */

  uint8_t lines = (height / 15) + 1;
  for(uint8_t i = 0; i < lines ; i++){
    int yPos = y + i * 15;
    if (yPos > y + height){
      break;
    }

    tft.drawFastHLine(x,y+(i*15),width, GRAY);

    float value = max - ((float)i / (lines - 1)) * (max - min);

    String str = String(value,1);

    tft.setCursor((x - 3)-(6*str.length()), (y+(i*15))-4);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    tft.print(value,1);
  }


  int oldX = 0;
  int oldY = 0;
  int newX = 0;
  int newY = 0;
  //iterating through data, drawing points on screen:
  for(uint16_t i = start; i<end; i++){

    // ( value-minimum ) / ( maximum-minimum )
    float relativePos = 1.0-(constrain((data[i]-min)/(max-min),0.0,1.0));

    if(i == 0){
      newX = x + 1 + (int)(((float)(i - start) * (width - 2)) / ((end - start) - 1) + 0.5);
      newY = y+7+((height-10)*relativePos);
    }else{
      oldX = newX;
      oldY = newY;
      newX = x + 1 + (int)(((float)(i - start) * (width - 2)) / ((end - start) - 1) + 0.5);
      newY = y+7+((height-10)*relativePos);

      tft.drawLine(oldX,oldY,newX,newY,color);
    }
  }

  //drawing bounding box:
  tft.drawRect(x,y,width+2,height,WHITE);
}