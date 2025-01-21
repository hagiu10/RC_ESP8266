// Include Arduino.h files in the header file for importing the Arduino library functions.
#include <Arduino.h>
#include <controlMotor.h>

/** Constructor  
 * This is the constructor for the controlMotor class.
 */
controlMotor::controlMotor() {
    // Constructor implementation
}
/** Initialize motor pins of esp8266
 * This function initializes the pins to controll pwm signal motor power.
 */
void controlMotor::init(void) {
    // Initialize the pins
    pinMode(D1, OUTPUT);  // sets the pin D1 as output
    pinMode(D2, OUTPUT);  // sets the pin D2 as output
    pinMode(D3, OUTPUT);  // sets the pin D3 as output
    pinMode(D4, OUTPUT);  // sets the pin D4 as output
    pinMode(D5, OUTPUT);  // sets the pin D5 as output
    pinMode(D6, OUTPUT);  // sets the pin D6 as output
    pinMode(D7, OUTPUT);  // sets the pin D7 as output
    pinMode(D8, OUTPUT);  // sets the pin D8 as output
    // Break all motors at the beginning
    breakAll();
}
/** Control front left motor
 * This function controls the front left motor.
 * @param dutyCycle The duty cycle of the pwm signal. Most be in range 0-255.
 * @param direction The direction of the motor. 0 - backward, 1 - forward
 */
void controlMotor::frontLeft(uint8_t dutyCycle, bool direction) {
    // Code to control the front left motor
    if(direction == FORWARD) {
        analogWrite(OUT3_MFLP, dutyCycle);
        analogWrite(OUT4_MFLN, 0);
    } else {
        analogWrite(OUT3_MFLP, 0);
        analogWrite(OUT4_MFLN, dutyCycle);
    }
#ifdef DEBUG
    Serial.print("Motor Front Left: ");
    Serial.printf("dutyCycle - %d",dutyCycle);
    Serial.print(" ");
    Serial.printf("direction - %d\n",direction);
#endif
}

/** Control front right motor
 * This function controls the front right motor.
 * @param dutyCycle The duty cycle of the pwm signal. Most be in range 0-255.
 * @param direction The direction of the motor. 0 - backward, 1 - forward
 */
void controlMotor::frontRight(uint8_t dutyCycle, bool direction) {
    // Code to control the front right motor
    if(direction == FORWARD) {
        analogWrite(OUT1_MFRP, dutyCycle);
        analogWrite(OUT2_MFRN, 0);
    } else {
        analogWrite(OUT1_MFRP, 0);
        analogWrite(OUT2_MFRN, dutyCycle);
    }
#ifdef DEBUG
    Serial.print("Motor Front Right: ");
    Serial.printf("dutyCycle - %d",dutyCycle);
    Serial.print(" ");
    Serial.printf("direction - %d\n",direction);
#endif
}

/** Control back left motor
 * This function controls the back left motor.
 * @param dutyCycle The duty cycle of the pwm signal. Most be in range 0-255.
 * @param direction The direction of the motor. 0 - backward, 1 - forward
 */
void controlMotor::backLeft(uint8_t dutyCycle, bool direction) {
    // Code to control the back left motor
    if(direction == FORWARD) {
        analogWrite(OUT6_MBLP, dutyCycle);
        analogWrite(OUT5_MBLN, 0);
    } else {
        analogWrite(OUT6_MBLP, 0);
        analogWrite(OUT5_MBLN, dutyCycle);
    }
#ifdef DEBUG
    Serial.print("Motor Back Left: ");
    Serial.printf("dutyCycle - %d",dutyCycle);
    Serial.print(" ");
    Serial.printf("direction - %d\n",direction);
#endif
}

/** Control back right motor
 * This function controls the back right motor.
 * @param dutyCycle The duty cycle of the pwm signal. Most be in range 0-255.
 * @param direction The direction of the motor. 0 - backward, 1 - forward
 */
void controlMotor::backRight(uint8_t dutyCycle, bool direction) {
    // Code to control the back right motor
    if(direction == FORWARD) {
        analogWrite(OUT7_MBRP, dutyCycle);
        analogWrite(OUT8_MBRN, 0);
    } else {
        analogWrite(OUT7_MBRP, 0);
        analogWrite(OUT8_MBRN, dutyCycle);
    }
#ifdef DEBUG
    Serial.print("Motor Back Right: ");
    Serial.printf("dutyCycle - %d",dutyCycle);
    Serial.print(" ");
    Serial.printf("direction - %d\n",direction);
#endif
}
/** Break all motors
 * This function breaks/stop all motors.
 */
void controlMotor::breakAll(void) {
    // Code to break all motors
    analogWrite(OUT1_MFRP, 0);
    analogWrite(OUT2_MFRN, 0);
    analogWrite(OUT3_MFLP, 0);
    analogWrite(OUT4_MFLN, 0);
    analogWrite(OUT5_MBLN, 0);
    analogWrite(OUT6_MBLP, 0);
    analogWrite(OUT7_MBRP, 0);
    analogWrite(OUT8_MBRN, 0);
#ifdef DEBUG
    Serial.println("Break all motors");
#endif
}