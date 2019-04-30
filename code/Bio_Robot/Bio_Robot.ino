#include <Servo.h>

Servo servos[8];
int zero[] = {95,90,65,115,40,60,116,120};
int lift_angle = 30;
int left_sweep = 25;
int right_sweep = 25;
int stepsize=(left_sweep+right_sweep)/9;
int lift_delay = 150;
int sweep_delay = 150;

void write_angles( double front_left_lift, double front_left_sweep, double front_right_sweep, double front_right_lift, double back_right_lift, double back_right_sweep, double back_left_sweep, double back_left_lift)
{
servos[ 0 ].write(front_left_lift);

servos[ 1 ].write(front_left_sweep);

servos[ 2 ].write(front_right_sweep); 

servos[ 3 ].write(front_right_lift); 

servos[ 4 ].write(back_right_lift);

servos[ 5 ].write(back_right_sweep);

servos[ 6 ].write(back_left_sweep);

servos[ 7 ].write(back_left_lift);


  
}


void setup() {
  // put your setup code here, to run once:
servos[ 0 ].attach( 3 );
servos[ 1 ].attach( 5 );
servos[ 2 ].attach( 4 );
servos[ 3 ].attach( 1 );
servos[ 4 ].attach( 6 );
servos[ 5 ].attach( 7 );
servos[ 6 ].attach( 8 );
servos[ 7 ].attach( 9 );


write_angles( zero[ 0 ],zero[ 1 ],
              zero[ 2 ],zero[ 3 ],
               zero[ 4 ],zero[ 5 ],
              zero[ 6 ], zero[ 7 ]);
}
void loop() {
  // Call the function for each leg phase
write_angles( zero[ 0 ]-lift_angle,left_sweep+zero[ 1 ],
              zero[ 2 ], -left_sweep+zero[ 3 ]+4*stepsize,
               zero[ 4 ], zero[ 5 ]-left_sweep+7*stepsize,
              zero[ 6 ]+left_sweep-stepsize, zero[ 7 ]);
delay(lift_delay);

}

