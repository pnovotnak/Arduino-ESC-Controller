#include <Servo.h> 
 
boolean debug   = true;
 
Servo ESC;  // create servo object to control the ESC
            // a maximum of eight servo objects can be created

int throttle_pin = 0;
int esc_pin      = 2;

int throttle_pos = 0;


int pos         = 50;    // variable to store the servo position (don't start at zero)
int throttle    = 0;

int output_min  = 50;
int output_max  = 180;

int throttle_min = 65;
int throttle_max = 950;

int sweep_delay = 15;
int sweep_min   = 0;
int sweep_max   = output_max;

int throttle_normalized;
int stale_throttle;

void sweep() {
  if (debug) {Serial.println("beginning sweep");}
  for(pos = sweep_min; pos < sweep_max; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree
    ESC.write(pos);               // tell servo to go to position in variable 'pos'
    if (debug) {Serial.print("sweeping up.. ");Serial.println(pos);}
    delay(sweep_delay);           // waits 15ms for the servo to reach the position 
  } 
  for(pos = sweep_max; pos >= sweep_min; pos-=1)  // goes from 180 degrees to 0 degrees 
  {     
    ESC.write(pos);               // tell servo to go to position in variable 'pos' 
    if (debug) {Serial.print("sweeping down.. "); Serial.println(pos);}
    delay(sweep_delay);           // waits 15ms for the servo to reach the position
  } 
}


int normalize_throttle(int throttle_val, int last_throttle) {
  if (throttle_val > throttle_max) {
    throttle_val = throttle_max;
  }
  
  if (throttle_val < throttle_min) {
    throttle_val = throttle_min;
  }
  
  if (throttle_val > last_throttle) {
    throttle_val = last_throttle + 1;
  }

  if (throttle_val < last_throttle) {
    throttle_val = last_throttle - 1;
  }

  return throttle_val;
}

void setup() {
  if (debug) {Serial.begin(9600);}
  ESC.attach(esc_pin);  // attaches the servo on pin 9 to the servo object
  if (debug) {Serial.println("attached to ESC");}
  ESC.write(pos);
  delay(4000);
  //sweep();
}


void loop() {
  if (debug) {
    //Serial.println("loop iteration");
  }
  throttle = analogRead(throttle_pin);

  Serial.println(throttle);

  throttle_normalized = map(
                            throttle,
                            throttle_min, throttle_max,
                            output_min, output_max
                        );
  
  throttle = normalize_throttle(throttle, stale_throttle);
  
  //Serial.println(throttle_normalized);

  ESC.write(throttle_normalized);
  stale_throttle = throttle_normalized;
  
  delay(15);
}
