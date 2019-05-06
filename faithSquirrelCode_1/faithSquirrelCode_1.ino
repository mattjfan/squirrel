#include <Servo.h>

#define MIN_ANGLE 0
#define MAX_ANGLE 180
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

void initialPosition() {
    setFrontLegs(45);
    setHindLegs(60,60);
}

void setup() {
  for (int i = 0; i<6; i++){ //initialize servos
    servos[i].attach(pins[i]);
  }
  initialPosition();
  delay(3000);
}

void loop() {

  int hl1 = 60;
  int hl2 = 60;
  int f = 45; 
  // 1st half of motion
  for (int i = 1; i <= 10; i++) {
    f = 45 + i*(152.0-45.0)/10.0; // changes from 45->145
    // first portion
    if (i <= 7) { // change top from 60->100
      hl1 += (150-60)/7;
      hl2 = 60;
      Serial.print("1st third");
    }
    // middle portion
    else if (i <= 8) { // bring leg up
      hl1 = 40; // bring to 40 degrees
      hl2 = 130; // bring to 140 degrees
    }
    else if (i <= 9) {
      hl1 = 20; // bring to 40 degrees
      hl2 = 20; // bring to 140 degrees
    }
    // last portion
    else {
      hl1 = 60; // bring to 60 degrees
      hl2 = 20; // bring to 60 degrees
      Serial.print("last third");
    }
    setHindLegs(hl1,hl2);
    setFrontLegs(f);
    delay(150);
  }
  
  // 2nd half of motion
  setHindLegs(60,90);
  delay(150);
  setFrontLegs(45);
  delay(150);

}
