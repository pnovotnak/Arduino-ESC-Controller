#include <Servo.h>

boolean debug   = false;

Servo ESC;  // create servo object to control the ESC
            // a maximum of eight servo objects can be created

int throttle_pin = 0;
int esc_pin      = 2;

int throttle_pos = 0;


int pos         = 0;    // variable to store the servo position (don't start at zero)
int throttle    = 0;

int output_min  = 35;
int output_max  = 160;

int throttle_min = 90;
int throttle_max = 950;

int sweep_delay = 12;
int sweep_min   = 0;
int sweep_max   = output_max;
int sweep_step  = 2;

int mapped_throttle;
int stale_throttle;



/*
 * Initialization function needed with some ESCs
*/
void sweep() {
  if (debug) Serial.println("beginning sweep");
  for(pos = sweep_min; pos < sweep_max; pos += sweep_step) {
    ESC.write(pos);
    if (debug) {Serial.print("sweeping up.. ");Serial.println(pos);}
    delay(sweep_delay);
  }
  for(pos = sweep_max; pos >= sweep_min; pos-=sweep_step) {
    ESC.write(pos);
    if (debug) {Serial.print("sweeping down.. "); Serial.println(pos);}
    delay(sweep_delay);
  }
}


/*
 * Normalzie a throttle input, to avoid crazyness from a dirty pot.
*/
int normalize_throttle(int throttle_val, int last_throttle) {

  // Change throttle
  if (throttle_val > last_throttle) {
    throttle_val = last_throttle + 2;

  }

  if (throttle_val < last_throttle) {
    throttle_val = last_throttle - 4;
  }

  // Keep the throttle within bounds
  if (throttle_val > output_max) {
    throttle_val = output_max;
  }

  if (throttle_val < output_min) {
    throttle_val = output_min;
  }

  return throttle_val;
}



void setup() {
  if (debug) Serial.begin(9600);
  ESC.attach(esc_pin);
  ESC.write(pos);
  sweep();
  delay(500);
}



void loop() {
  //if (debug) Serial.println("loop iteration");

  throttle = analogRead(throttle_pin);

  //if (debug) Serial.println(throttle);

  mapped_throttle = map(
                        throttle,
                        throttle_min,
                        throttle_max,
                        output_min,
                        output_max
                    );

  throttle = normalize_throttle(mapped_throttle, stale_throttle);

  if (debug) {Serial.print(mapped_throttle);Serial.print(" - ");Serial.println(throttle);}

  if (stale_throttle != throttle) {
    ESC.write(throttle);
  }

  stale_throttle = throttle;
  delay(15);
}
