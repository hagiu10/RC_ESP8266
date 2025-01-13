#include <blinkLed.h>
#include <controlMotor.h>
#include <SN74HC595N.h>
#include <millisDelay.h>
#include <readVoltage.h>

#define DEBUG

blinkLed blinkLedD2; // create an instance of the blinkLed class
millisDelay mainDelay; // the delay object, the overall delay
controlMotor motor; // create an instance of the controlMotor class
sn74hc595n sn74h; // create an instance of the sn74hc595n class
motorUpDown motorM3; // create an instance of the motorUpDown class
readVoltage voltage; // create an instance of the readVoltage class

// the setup function runs once when you press reset or power the board
void setup() {
#ifdef DEBUG
  // Serial port for debugging purposes
  Serial.begin(115200);
#endif
  blinkLedD2.init();
  motor.init();
  sn74h.init();
  voltage.init();
  delay(1000);
 
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Start motor up and down");
  motorM3.start();
  voltage.readVoltageBat();
  delay(1000);
  Serial.println("Stop motor up and down");
  motorM3.stop();
  voltage.readVoltageBat();
  delay(1000);
  // Serial.println("Forward");
  // motor.frontLeft(255, FORWARD);
  // motor.frontRight(255, FORWARD);
  // motor.backLeft(125, FORWARD);
  // motor.backRight(125, FORWARD);
  // delay(7000);
  // motor.breakAll();
  // delay(1000);
  // //blinkLedD2.start(5000);
  // Serial.println("Backward");
  // motor.frontLeft(255, BACKWARD);
  // motor.frontRight(255, BACKWARD);
  // motor.backLeft(125, BACKWARD);
  // motor.backRight(125, BACKWARD);
  // delay(7000);
  // motor.breakAll();
  // delay(1000);
}