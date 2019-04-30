/*
 * Bio-Inspired Squirrel Robot (ENME489L Bio-inspired Robotics Final Project)
 * by Matt Fan
 * 
 * It's a squirrel!
 * 
 */
#include <Servo.h>

#define MIN_ANGLE 20
#define MAX_ANGLE 150
#define LEFT 0
#define RIGHT 1
#define LEN_F 102
#define LEN_BU 89
#define LEN_BL 86

Servo servos[6];
int pins[6] = {3,5,6,9,10,11};

void setAngle(int motor, int angle){
  // writes the angle
  // angle = 0 corresponds to furthest angular extent to the FRONT
  // angle = 180 corresponds to furthest angular extent to the BACK
  if (motor % 2 == LEFT){ // Left side motors are even
    servos[motor].write(angle + MIN_ANGLE);
  } else if (motor % 2 == RIGHT){ // Right side motors are odd
    servos[motor].write(MAX_ANGLE - angle);
  }
}

void setFrontLegs(int angle){
  setAngle(0, angle);
  setAngle(1, angle);
}

void setHindLegs(int angle_upper, int angle_lower){
  setAngle(2, angle_upper);
  setAngle(3, angle_upper);
  setAngle(4, angle_lower);
  setAngle(5, angle_lower);
}

int retrieveAngle(int motor) {
  // servo.read(), but with angle adjustments accounted for
  return motor % 2 == LEFT ? servos[motor].read() - MIN_ANGLE : MAX_ANGLE - servos[motor].read();
}

void bend(int height){
  int h_left = LEN_F * sin(float(servos[0].read() * PI) / 180);
  int h_right  =  LEN_F * sin(float(servos[1].read() * PI) / 180);
}

void setAngleAll(int angle){
  for (int i = 0; i < 6; i++){
    setAngle(i, angle);
  }
}

void setup() {
  for (int i = 0; i<6; i++){ //initialize servos
    servos[i].attach(pins[i]);
  }
  setAngleAll(0);
  //@TODO: initialize sensor
}

void loop() {
  setFrontLegs(120);
  delay(0);
  setHindLegs(0,90);
  delay(200);
  setHindLegs(0,0);
  delay(150);
  setFrontLegs(30);
  delay(50);
  setHindLegs(110,0);
  delay(300);
}
