#include <Servo.h>

Servo lbu;  // create servo object to control a servo
Servo lbl;
// twelve servo objects can be created on most boards
int angle_offset = 20;
int max_angle = 145;
int pos = 0;    // variable to store the servo position
int len_upper = 40;
int len_lower = 40;
int ht = 100;
void setup() {
  lbu.attach(9);  // attaches the servo on pin 9 to the servo object
  lbl.attach(10);
  lbu.write(90+angle_offset);
  lbl.write(angle_offset);  
}
void writeAdjusted(Servo servo, int angle) {
  // kludge wrapper to restrict pulse limits and write the angle in real bounds :(
  int new_angle = angle;
  new_angle = new_angle > 0 ? new_angle : 0;
  new_angle = new_angle + angle_offset;
  new_angle = new_angle <= max_angle ? new_angle : max_angle;
  servo.write(new_angle);
  
}
void setKinematicStep(int angle_upper, int target_height, boolean concave) {
  // Specify angle from -a to +a (where a is roughly 60)
  // Will try to match lower joint parameter to achieve desired height with given upper joint parameter
  // If angle is out of bounds, will go to 'closest' option.
  writeAdjusted(lbu, 90 + angle_offset + angle_upper);
  int h_lower = target_height - len_upper * cos(PI * angle_upper / 180); //estimate lower leg desired height;
  int projected_angle = acos(float(h_lower)/float(len_lower))* 180 / PI;
  if (concave) {
    writeAdjusted(lbl, projected_angle + angle_upper + angle_offset);
  } else {
    writeAdjusted(lbl, angle_upper + angle_offset - projected_angle);
  }
}

void KinematicAngleSweep(int start_angle, int end_angle, int height){
  // Assumes concave leg configuration
  if (end_angle < start_angle) { // avoid infinite loop
    end_angle = start_angle; // set kinematic position to start_angle only, no sweep 
  }
  int angle = start_angle;
  while (angle <= end_angle) {
    setKinematicStep(angle, height, true);
    angle++;
    delay(5);
  }
}

void KinematicAngleSweepWithPropulsion(int start_angle, int end_angle, int height, int height_delta){
  // Assumes concave leg configuration
  // Prob could just use a simple circular sweep in this case, but...
  if (end_angle < start_angle) { // avoid infinite loop
    end_angle = start_angle; // set kinematic position to start_angle only, no sweep 
  }
  int angle = start_angle;
  int curr_height = height;
  while (angle <= end_angle) {
    setKinematicStep(angle, curr_height, true);
    angle++;
    height = height + height_delta * angle / (end_angle - start_angle + 1);
    delay(5);
  }
}

void setHindLegs(int angle_upper, int angle_lower){
  lbu.write(angle_upper+angle_offset);
  lbl.write(angle_lower+angle_offset);
}
void loop() {
//  setHindLegs(60,30);
//  delay(300);
  setHindLegs(0,90);
  delay(200);
  setHindLegs(0,0);
  delay(200);
  setHindLegs(110,0);
  delay(400);
//setHindLegs(0,0);
}
