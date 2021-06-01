#include<math.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define arm1 11.7
#define arm2 11.3
#define grip 12
#define ALPHA_LOW 0.79
#define ALPHA_HIGH 1.02
#define DISTANCE_TO_BOARD 10.0
#define TILE_SIZE 2.0

SoftwareSerial esp32(4, 3);

enum componentNames {BASE = 0, ARM_ROTATION_1, ARM_ROTATION_2, WRIST_LEFTROTATION,WRIST_UPROTATION,GRIP};

Servo components[6];

double tanAlphaLow = 0.0;
double tanAlphaHigh = 0.0;

void writeSmooth(int endPosition, int index, int countSteps = 6) 
{
  int currentAngle = components[index].read();

  float delta = (endPosition - currentAngle)/countSteps;
  for(int i=0;i<countSteps;++i)
  {
    currentAngle+= delta;
    components[index].write(currentAngle);
    delay(100);
  }
  components[index].write(endPosition);
}

void setBaseRotation(int row, int column) {
  double tanAlpha = tanAlphaLow + (row / 7.0) * (tanAlphaHigh - tanAlphaLow);
  double baseRotation = atan((tanAlpha*(7 - 2*column))/(tanAlpha*(2*row+1)+8));
  writeSmooth(88 - 3 * (row / 7.0) +(baseRotation*180/M_PI),BASE, 6);
}

void setAngles(double shoulder, double elbow, double wrist) {
  writeSmooth(wrist,WRIST_UPROTATION);
  writeSmooth(elbow,ARM_ROTATION_2);
  writeSmooth(shoulder,ARM_ROTATION_1);
  writeSmooth(0,WRIST_LEFTROTATION);
}

void defaultAngles() {
  writeSmooth(80,ARM_ROTATION_1);
  writeSmooth(100,ARM_ROTATION_2);
  writeSmooth(40,WRIST_UPROTATION);
  writeSmooth(0,WRIST_LEFTROTATION);
}

double commands[8][4][3] =
  {
    //Row 1
    {
      {78, 137, 49},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {66, 127, 47},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {59, 112, 41},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {52, 100, 40},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {38, 66, 19},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {24, 39, 8},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {17, 29, 11},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    {
      {15, 28, 24},
      {90, 0, 90},
      {90, 0, 90},
      {90, 0, 90},
    },
    //Row 2
  };

void applyAngles(int row, int col) {
  int cmdCol = col;
  if(col > 3) {
    cmdCol = 7 - col;
  }
  setAngles(commands[row][cmdCol][0], commands[row][cmdCol][1], commands[row][cmdCol][2]);
}

void grab() {
  writeSmooth(9,GRIP);
}

void ungrab() {
  writeSmooth(40,GRIP);
}

void setPosition(int row, int col) {
  setBaseRotation(row, col);
  //delay(2000); 
  applyAngles(row, col);
  //delay(2000);
}

void makeTurn(int row0, int col0, int row, int col) {
  setPosition(row0, col0);
  grab();
  
  defaultAngles();
  
  setPosition(row, col);
  ungrab();
  
  defaultAngles();
}

void setup() {
  Serial.begin(9600);
  esp32.begin(38400);

  tanAlphaLow = tan(ALPHA_LOW);
  tanAlphaHigh = tan(ALPHA_HIGH);
  // put your setup code here, to run once:
  for(int i=0;i<6;++i)
  {
    components[i].attach(i+8);      
  }

  defaultAngles();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*GoTo(0);
  delay(1000);
  GoTo(7);
  delay(1000);
  GoTo(56);
  delay(1000);
  GoTo(63);
  delay(1000);
  */
  //components[BASE].write(0);
  //GoTo(0);
  //components[BASE].write(90);
  //
//  for(int i=0;i<64;++i){
//    GoTo(i);
//    delay(1000);
//  }
//  delay(1000);
//  //components[BASE].write(90);
//  delay(1000);
 
  makeTurn(0, 7, 7, 0);
  makeTurn(7, 0, 7, 7);
  makeTurn(7, 7, 0, 0);
  makeTurn(0, 0, 0, 7);

//  int row = 0;
//  makeTurn(row, 7, row, 0);
//  makeTurn(row, 0, row, 7);

//  setAngles(90, 0, 90);
//  delay(1000);

//  if (esp32.available()) {
//    Serial.println(esp32.read());
//  }

}
