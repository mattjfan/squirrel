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
int target_angle[6];

void setAngle(int motor, int angle){
  // writes the angle
  // angle = 0 corresponds to furthest angular extent to the FRONT
  // angle = 180 corresponds to furthest angular extent to the BACK
  if (motor % 2 == LEFT){ // Left side motors are even
    servos[motor].write(angle + MIN_ANGLE);
  } else if (motor % 2 == RIGHT){ // Right side motors are odd
    servos[motor].write(MAX_ANGLE - angle);
  }
  target_angle[motor] = angle;
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
  //  return motor % 2 == LEFT ? servos[motor].read() - MIN_ANGLE : MAX_ANGLE - servos[motor].read();
  return target_angle[motor];
}

void bend(){
  // Take front leg positions, and calculate back leg joint angles to lie 'flat' through inverse kinematics
  // Bend position is additionally constrained so that shoulder and foot are laterally coincident (i.e. share a vertical axis)
  int h_left = LEN_F * sin(float(servos[0].read() * PI) / 180);
  int h_right  =  LEN_F * sin(float(servos[1].read() * PI) / 180);
  setAngle(2, 180 * acos((LEN_BU*LEN_BU + h_left*h_left - LEN_BL*LEN_BL) / (2*LEN_BU*h_left)) / PI);
  setAngle(3, 180 * acos((LEN_BU*LEN_BU + h_right*h_right - LEN_BL*LEN_BL) / (2*LEN_BU*h_right)) / PI);
  setAngle(4, 180 * acos((h_left*h_left - LEN_BU*LEN_BU - LEN_BL*LEN_BL) / (2*LEN_BU*LEN_BL)) / PI);
  setAngle(5, 180 * acos((h_right*h_right - LEN_BU*LEN_BU - LEN_BL*LEN_BL) / (2*LEN_BU*LEN_BL)) / PI);
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
//  setAngleAll(0);
  setFrontLegs(70);
  bend();
  delay(1000);
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
  setHindLegs(130,0);
  delay(350);
}
