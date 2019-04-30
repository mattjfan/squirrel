#include <MPU9250.h>

#define LBU 1
#define LBL 0
#define LFL 0
#define LFR 0

int t_lbu; // precalculated pulse periods for each servo group
int t_lbl; // in microseconds
int t_lfl;
int t_lfr;
long t0;
long t_elapsed;
void setup() {
  // put your setup code here, to run once:
  pinMode(LBU, OUTPUT);
  pinMode(LBL, OUTPUT);
  pinMode(LFL, OUTPUT);
  pinMode(LFR, OUTPUT);
}

int angleToPeriod(int angle){
  return 1000 * angle / 180 + 1000;
}

void setBackLeg(int upper_angle, int lower_angle){
  t_lbu = angleToPeriod(upper_angle);
  t_lbl = angleToPeriod(lower_angle);
}

void servoDelay(long millisecondsToDelay){
  long microsecondsToDelay = 1000 * millisecondsToDelay;
  t0 = micros();
  while (micros() - t0 < microsecondsToDelay) {
    if ((micros() - t0) % 20000 <= t_lbu){
      digitalWrite(LBU, HIGH);
    } else {
      digitalWrite(LBU, LOW);
    }

    if ((micros() - t0) % 20000 <= t_lbl){
      digitalWrite(LBL, HIGH);
    } else {
      digitalWrite(LBL, LOW);
    }

    if ((micros() - t0) % 20000 <= t_lfl){
      digitalWrite(LFL, HIGH);
    } else {
      digitalWrite(LFL, LOW);
    }

    if ((micros() - t0) % 20000 <= t_lfr){
      digitalWrite(LFL, HIGH);
    } else {
      digitalWrite(LFL, LOW);
    }
  }
}
void loop() {
 setBackLeg(90,0);
 servoDelay(400);
 setBackLeg(0,90);
 servoDelay(200);
 setBackLeg(0,0);
 servoDelay(200);
}
