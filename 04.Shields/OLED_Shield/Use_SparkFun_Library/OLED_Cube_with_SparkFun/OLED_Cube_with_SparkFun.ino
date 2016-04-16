#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////

MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example

int SCREEN_WIDTH = oled.getLCDWidth();
int SCREEN_HEIGHT = oled.getLCDHeight();

float d = 3;
float px[] = { 
  -d,  d,  d, -d, -d,  d,  d, -d };
float py[] = { 
  -d, -d,  d,  d, -d, -d,  d,  d };
float pz[] = { 
  -d, -d, -d, -d,  d,  d,  d,  d };

float p2x[] = {
  0,0,0,0,0,0,0,0};
float p2y[] = {
  0,0,0,0,0,0,0,0};

float r[] = {
  0,0,0};

#define SHAPE_SIZE 600
// Define how fast the cube rotates. Smaller numbers are faster.
// This is the number of ms between draws.
#define ROTATION_SPEED 0

void setup()
{
  oled.begin();
  oled.clear(ALL);
  oled.display();  
}

void loop()
{
  drawCube();
  delay(ROTATION_SPEED);
}

void drawCube()
{
  r[0]=r[0]+PI/180.0; // Add a degree
  r[1]=r[1]+PI/180.0; // Add a degree
  r[2]=r[2]+PI/180.0; // Add a degree
  if (r[0] >= 360.0*PI/180.0) r[0] = 0;
  if (r[1] >= 360.0*PI/180.0) r[1] = 0;
  if (r[2] >= 360.0*PI/180.0) r[2] = 0;

  for (int i=0;i<8;i++)
  {
    float px2 = px[i];
    float py2 = cos(r[0])*py[i] - sin(r[0])*pz[i];
    float pz2 = sin(r[0])*py[i] + cos(r[0])*pz[i];

    float px3 = cos(r[1])*px2 + sin(r[1])*pz2;
    float py3 = py2;
    float pz3 = -sin(r[1])*px2 + cos(r[1])*pz2;

    float ax = cos(r[2])*px3 - sin(r[2])*py3;
    float ay = sin(r[2])*px3 + cos(r[2])*py3;
    float az = pz3-150;

    p2x[i] = SCREEN_WIDTH/2+ax*SHAPE_SIZE/az;
    p2y[i] = SCREEN_HEIGHT/2+ay*SHAPE_SIZE/az;
  }

  oled.clear(PAGE);
  for (int i=0;i<3;i++) 
  {
    oled.line(p2x[i],p2y[i],p2x[i+1],p2y[i+1]);
    oled.line(p2x[i+4],p2y[i+4],p2x[i+5],p2y[i+5]);
    oled.line(p2x[i],p2y[i],p2x[i+4],p2y[i+4]);
  }    
  oled.line(p2x[3],p2y[3],p2x[0],p2y[0]);
  oled.line(p2x[7],p2y[7],p2x[4],p2y[4]);
  oled.line(p2x[3],p2y[3],p2x[7],p2y[7]);
  oled.display();
}

