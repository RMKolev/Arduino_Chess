#include<math.h>
#include <Servo.h>
#define arm1 11.7
#define arm2 11.3
#define grip 12
#define ALPHA 1.09
#define START_BOARD_OFFSET 30
struct Point {
  float x;
  float y;

  Point(float x, float y) : x(x),y(y) {};
};
enum componentNames {BASE = 0, ARM_ROTATION_1, ARM_ROTATION_2, WRIST_LEFTROTATION,WRIST_UPROTATION,GRIP};

Servo components[6];

double tanAlpha = 0.0;

void GetAngles(float& alpha, float& beta, float& gamma, Point endPoint)
{
  //float 
}
void GoTo (int index) 
{
  int row = index/8;
  int column = index%8;
  
  //BASE ROTATION
  double baseRotation = atan((tanAlpha*(7 - 2*column))/(tanAlpha*(2*row+1)+8));
  components[BASE].write(90+(baseRotation*180/M_PI));
  Serial.println((baseRotation*180/M_PI));

  components[ARM_ROTATION_1].write(0);
  components[ARM_ROTATION_2].write(0);
  components[WRIST_LEFTROTATION].write(0);
  components[WRIST_UPROTATION].write(0);
}


void setup() {
  Serial.begin(9600);

  tanAlpha = tan(ALPHA);
  // put your setup code here, to run once:
  for(int i=0;i<6;++i)
  {
    components[i].attach(i+8);      
  }
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
  for(int i=0;i<64;++i){
    GoTo(i);
    delay(1000);
  }
  delay(1000);
  //components[BASE].write(90);
  delay(1000);
}
