#include<math.h>
#include <Servo.h>
#define arm1 11.7
#define arm2 11.3
#define grip 12
#define ALPHA 0.7
#define START_BOARD_OFFSET 30
#define DISTANCE_TO_BOARD 10.0
#define TILE_SIZE 4.0

#define A 12.0
#define B 12.0
#define P 1.0

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

  //ARM ROTATIONS
  double length_to_tile_squared = pow(abs((3.5 - column) * TILE_SIZE), 2) + pow((DISTANCE_TO_BOARD + row + 0.5), 2);
  double C = sqrt(length_to_tile_squared + P * P);

  double arm_rotation_1 = (acos((A*A + C*C - B*B) / (2 * A * C)) + asin(P / C)) * 180 / M_PI;
  double arm_rotation_2 = 180 - acos((A*A + B*B - C*C)/(2 * A * B)) * 180 / M_PI;
  double wrist_rotation = (M_PI - acos((B*B + C*C - A*A)/(2 * B * C)) - acos(P / C)) * 180 / M_PI - 90;

  components[ARM_ROTATION_1].write(arm_rotation_1);
  components[ARM_ROTATION_2].write(arm_rotation_2);
  components[WRIST_LEFTROTATION].write(0);
  components[WRIST_UPROTATION].write(wrist_rotation);
  components[GRIP].write(30);
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
