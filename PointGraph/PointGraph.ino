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
    arr[i] = sin(i/10.0)*200;
  }
}

void setup() {
  tft.begin(0x9325);

  tft.reset();
  tft.fillScreen(0x0000);
}

void loop() {
  float data[200];
  fillRandomFloatArray(data, 200);

  tft.fillScreen(BLACK);

  drawPointDiagram(55, 20, 175, 75, data, 0, 200, 0xF456);

  delay(5000);
}

//This needs more memory optimization. After stress-testing it seems to be able to handle ~400 data values in the array.
void drawPointDiagram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, uint16_t color){

  /*tft.drawFastVLine(x-2,y-2,height+6,WHITE);
  tft.drawFastVLine(x-3,y-2,height+6,WHITE);*/

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

  uint8_t lines = (height / 15) + 1;
  for(uint8_t i = 0; i < lines ; i++){
    int yPos = y + i * 15;
    if (yPos > y + height){
      break;
    }

    tft.drawFastHLine(x,y+(i*15),width, GRAY);

    float value = max_num - ((float)i / (lines - 1)) * (max_num - min_num);

    String str = String(value,1);

    tft.setCursor((x - 3)-(6*str.length()), (y+(i*15))-4);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    tft.print(value,1);
  }

  /*
  //CHATGPT CODE, REPLACE LATER!!!111!!!:
  uint8_t lineCount = height / 15; // or however many lines you want
for (uint8_t i = 0; i <= lineCount; i++) {
    uint16_t yLine = y + i * 15;
    tft.drawFastHLine(x, yLine, width, GRAY);

    // normalized position from top
    float relativePos = 1.0f - ((float)(i*15) / (height-15)); 
    int lineValue = round(min_num + relativePos * (max_num - min_num));

    // draw text to the left
    tft.setCursor(x - 17, yLine - 4);  // tweak offsets to fit
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    tft.print(lineValue);           // 1 decimal place
}

*/

  //iterating through data, drawing points on screen:
  for(uint16_t i = start; i<end; i++){

    // ( value-minimum ) / ( maximum-minimum )
    float relativePos = 1.0-(constrain((data[i]-min_num)/(max_num-min_num),0.0,1.0));

    tft.fillCircle(
      /* 
      x + 1 is the starting position.
      (int) turns everything in the next parantheses into an integer, essentially cutting off the decimal point. This is why you have (+0.5) at the end, so it essentially acts as rounding.
      (float) turns the next parantheses, (i-start) into floating point numbers, allowing for precise calculation.
      (i - start)*(width - 2) is basically the position of the point. width has subtracted 2 in order to cut off 2 pixels.
      / (end-start) is how long the graph is, it needs to divide to see how much space should be between each point.
      */
      x + 1 + (int)(((float)(i - start) * (width - 2)) / ((end - start) - 1) + 0.5),
      y+7+((height-10)*relativePos),
      1,
      color
    );
  }

  //drawing bounding box:
  tft.drawRect(x,y,width+2,height,WHITE);
}