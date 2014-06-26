#include <Servo.h> 
 
 
Servo ESC;  // create servo object to control the ESC
            // a maximum of eight servo objects can be created

int throttle_pin = 13;
int throttle_pos = 0;


int pos         = 0;    // variable to store the servo position (don't start at zero)
int sweep_delay = 2;
int sweep_min   = 0;
int sweep_max   = 180;

boolean debug   = true;

void sweep() {
  if (debug) {Serial.print('attached to ESC');}
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    ESC.write(pos);               // tell servo to go to position in variable 'pos' 
    delay(sweep_delay);           // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)  // goes from 180 degrees to 0 degrees 
  {                                
    ESC.write(pos);               // tell servo to go to position in variable 'pos' 
    delay(sweep_delay);           // waits 15ms for the servo to reach the position 
  } 
}


void setup() { 
  if (debug) {Serial.begin(4800);}
  ESC.attach(2);  // attaches the servo on pin 9 to the servo object
  if (debug) {Serial.print('attached to ESC');}
  sweep();
}


void loop() {
  if (debug) {
    Serial.print('loop iteration');
  }
}
