#include "TFTGraph.h"
#include "math.h"

//Gauge:
static double sind(double deg);
static double cosd(double deg);
static void drawHalfCircle(Adafruit_GFX &gfx, uint16_t xc, uint16_t yc, uint8_t r, uint16_t color);

//Line/Point diagram:
static void drawDiagramBody(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max);

void drawGauge(Adafruit_GFX &gfx,
                            uint16_t x, uint16_t y, uint8_t r,
                            float value, float min,
                            float max, uint16_t color) {
    drawHalfCircle(gfx,x,y,r,0xFFFF);

  //Drawing gauge line:
  int Ang = 260 + ((value - min) * (100 - 260)) / (max - min);
  gfx.drawLine(
    x,
    y,
    x+sind(Ang)*(r-(r/5)),
    y+cosd(Ang)*(r-(r/5)),
    color);

  //draw base of arrow (simple point):
  gfx.drawFastHLine(x-1,y,3,0xFFFF);
  gfx.drawFastVLine(x,y-1,3,0xFFFF);

  float step = (max - min) / 8;
  float currentStep = min;

  //draw text:
  for(int i = 26; i>9; i--){

    bool offset = false;
    if(i<=16){
      offset = true;
    }

    //Only draw if "i" is an even number (drawing every iteration would get a bit much.)
    if( i % 2 == 0){
      gfx.setCursor(
        x+sind(i*10)*(r-5)+((String(currentStep).length()*2)*(offset*-1)),
        y+cosd(i*10)*(r-5));
      gfx.setTextColor(0xFFFF);
      gfx.setTextSize(1);
      gfx.print(currentStep,0);
      currentStep += step;
    }
  }
}

static void drawHalfCircle(Adafruit_GFX &gfx,
                                            uint16_t xc, uint16_t yc,
                                            uint8_t r, uint16_t color){

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

//Helper functions:
static double sind(double deg) {
    return sin(deg * M_PI / 180.0);
}

static double cosd(double deg) {
    return cos(deg * M_PI / 180.0);
}

void drawPointDiagram(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color){
  //"Cleaning" some values:
  x = max(0,x);
  y = max(0,y);
  width = max(5,width);
  height = max(5,height);
  start = min(start, end);
  min = min(min, max);

  drawDiagramBody(gfx, x, y, width, height, min, max);

  //iterating through data, drawing points on screen:
  for(uint16_t i = start; i<end; i++){

    // ( value-minimum ) / ( maximum-minimum )
    float relativePos = 1.0-(constrain((data[i]-min)/(max-min),0.0,1.0));

    gfx.fillCircle(
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
}

void drawLineDiagram(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float data[], uint16_t start, uint16_t end, float min, float max, uint16_t color){

  //"Cleaning" some values:
  x = max(0,x);
  y = max(0,y);
  width = max(5,width);
  height = max(5,height);
  start = min(start, end);
  min = min(min, max);

  drawDiagramBody(gfx, x, y, width, height,min, max);

  int oldX = 0;
  int oldY = 0;
  int newX = 0;
  int newY = 0;
  //iterating through data, drawing points on screen:
  for(uint16_t i = start; i<end; i++){

    // ( value-minimum ) / ( maximum-minimum )
    float relativePos = 1.0-(constrain((data[i]-min)/(max-min),0.0,1.0));

    if(i == start){
      newX = x + 1 + (int)(((float)(i - start) * (width - 2)) / ((end - start) - 1) + 0.5);
      newY = y+7+((height-10)*relativePos);
    }else{
      oldX = newX;
      oldY = newY;
      newX = x + 1 + (int)(((float)(i - start) * (width - 2)) / ((end - start) - 1) + 0.5);
      newY = y+7+((height-10)*relativePos);

      gfx.drawLine(oldX,oldY,newX,newY,color);
      gfx.drawLine(oldX,oldY-1,newX,newY-1,color);
    }
  }
}

static void drawDiagramBody(Adafruit_GFX &gfx, uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max){
    uint8_t lines = (height / 15) + 1;
  for(uint8_t i = 0; i < lines ; i++){
    int yPos = y + i * 15;
    if (yPos > y + height){
      break;
    }

    gfx.drawFastHLine(x,y+(i*15),width, 0x8410);

    float value = max - ((float)i / (lines - 1)) * (max - min);

    String str = String(value,1);

    gfx.setCursor((x - 3)-(6*str.length()), (y+(i*15))-4);
    gfx.setTextColor(0xFFFF);
    gfx.setTextSize(1);
    gfx.print(value,1);
  }

  //drawing bounding box:
  gfx.drawRect(x,y,width+2,height,0xFFFF);
}

void drawPieChart(Adafruit_GFX &gfx,int x, int y, uint8_t r, float data[], int start, int end, uint16_t colors[]) {

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

    /*gfx.drawLine(x,y,
    x+cosd(currentAngle)*r, y+sind(currentAngle)*r,
    colors[i]);*/

    //filling in colors:
    //MAJOR OPTIMIZATION IS NEEDED HERE:
    /*Ideas:
    - Draw only a quarter of the circle at once depending on the angle.
    - Use fastHLine and fastVLine(No idea how to implement this.)
    - Artificially decrease resolution (have 2x2 pixels instead of 1x1)
    */
    for (int i2 = 0; i2 < r * 2; i2++) {
      for (int i3 = 0; i3 < r * 2; i3++) {
        //skipping half of the pixels to speed up drawing:
        if ((i2 + i3) % 2 == 0) continue;

        //getting current coordinates relative to x and y center:
        int px = (x - r) + i2;
        int py = (y - r) + i3;

        int dx = px - x;
        int dy = py - y;

        float distance = sqrtf(dx * dx + dy * dy);
        //if distance is over, skip this iteration:
        if (distance > r){
          continue;
        }

        //calculating angle from center to current pixel:
        float angle = atan2(dy, dx) * 180.0 / PI;
        if (angle < 0){
          angle += 360;
        }
        
        //if angle is within slice, and the distance is within the circle, draw a pixel:
        if (angle >= currentAngle && angle < currentAngle + angleAdd) {
          gfx.drawPixel(px, py, colors[i]);
        }
      }
    }

    //first drawing square of color:
    gfx.fillRect(x+r+8,(y-(r-10))+((i-start)*11),4,4,colors[i]);

    //drawing text:
    gfx.setCursor(x+r+14,((y-(r-10))-2)+((i-start)*11));
    gfx.setTextSize(1);
    gfx.setTextColor(0xFFFF);
    float percent = (angleAdd / 360.0) * 100.0;
    gfx.print(percent, 1);
    gfx.print("%");

    currentAngle += angleAdd;
  }
  //draw bounding circle:
  //gfx.drawCircle(x,y,r,0xFFFF);
}