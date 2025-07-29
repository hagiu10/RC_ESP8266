#include <motorControl.h>

#ifdef DEBUG
bool incDutyCycleMotor = true; // Initialize the global variable
uint8_t dutyCycleMotor = PWM_MIN_DUTY_CYCLE; // Initialize the global variable
#endif

/** Constructor  
 * This is the constructor for the motorControl class.
 */
motorControl::motorControl() {
    // Constructor implementation
    _frontLeftMotor.pinPositive = OUT3_MFLP;
    _frontLeftMotor.pinNegative = OUT4_MFLN;
    _frontRightMotor.pinPositive = OUT1_MFRP;
    _frontRightMotor.pinNegative = OUT2_MFRN;
    _backLeftMotor.pinPositive = OUT6_MBLP;
    _backLeftMotor.pinNegative = OUT5_MBLN;
    _backRightMotor.pinPositive = OUT7_MBRP;
    _backRightMotor.pinNegative = OUT8_MBRN;
#ifdef DEBUG
    Serial.printf("motorControl: Constructor called. [%lu ms]\n", millis());
#endif
}
/** Initialize motor pins of esp8266
 * This function initializes the pins to controll pwm signal motor power.
 */
void motorControl::init(void) {
    // Initialize the pwm signal
    pwmSignal::init();
    // Initialize the shift register
    sn74hc595n::init();
    // Initialize the pins
    pinMode(D1, OUTPUT);  // sets the pin D1 as output
    pinMode(D2, OUTPUT);  // sets the pin D2 as output
    pinMode(D3, OUTPUT);  // sets the pin D3 as output
    pinMode(D4, OUTPUT);  // sets the pin D4 as output
    pinMode(D5, OUTPUT);  // sets the pin D5 as output
    pinMode(D6, OUTPUT);  // sets the pin D6 as output
    pinMode(D7, OUTPUT);  // sets the pin D7 as output
    pinMode(D8, OUTPUT);  // sets the pin D8 as output
#ifdef DEBUG
    Serial.printf("motorControl: Initialized all pins for motors control. [%lu ms]\n", millis());
#endif
    // Break all motors at the beginning
    breakAll();
}  
/** Control speed and direction of motor
 * This function control the speed and direction of motor.
 * @param motor The motor to be controlled
 * @param dutyCycle The duty cycle of the pwm signal. Most be in range 0-100.
 * @param direction The direction of the motor. 0 - backward, 1 - forward
 */
void motorControl::setSpeed(motor motor, uint8_t dutyCycle, bool direction) {
    // Code to control the motor
    if (direction == FORWARD) {
        setDutyCycle(motor.pinPositive, dutyCycle);
        setDutyCycle(motor.pinNegative, 0);
    } else {
        setDutyCycle(motor.pinPositive, 0);
        setDutyCycle(motor.pinNegative, dutyCycle);
    }
#ifdef DEBUG
    Serial.printf("motorControl: Set speed called. [%lu ms]\n", millis());
#endif
}
/** Move the motor up and down
 * This function moves the motor up and down.
 * @param state The state of the motor. 0 - stop, 1 - start
 */
void motorControl::upDown(bool state) {
    // Code to move the motor up and down
    if (state) {
        setBitRegState(Q5_MOTOR, HIGH);
    } else {
        setBitRegState(Q5_MOTOR, LOW);
    }
#ifdef DEBUG
    Serial.printf("motorControl::upDown Move the motor up and down called with state: %d. [%lu ms]\n",state, millis());
#endif
}
/** Break all motors
 * This function breaks/stop all motors.
 */
void motorControl::breakAll(void) {
    // Code to break all motors
    setDutyCycle(OUT1_MFRP, 0);
    setDutyCycle(OUT2_MFRN, 0);
    setDutyCycle(OUT3_MFLP, 0);
    setDutyCycle(OUT4_MFLN, 0);
    setDutyCycle(OUT5_MBLN, 0);
    setDutyCycle(OUT6_MBLP, 0);
    setDutyCycle(OUT7_MBRP, 0);
    setDutyCycle(OUT8_MBRN, 0);
    upDown(false);
#ifdef DEBUG
    Serial.printf("motorControl: Break all motors called. All pins are seting to LOW. [%lu ms]\n", millis());
#endif
}
/** Get instance of the motorControl
 * This function returns the instance of the motorControl class.
 * @return The instance of the motorControl class
 */
motorControl* motorControl::_getInstance(void) {
    static motorControl instance;
    return &instance;
}
/** Test all motors using pwm signal 
 * This function tests all motors using pwm signal.
 * this function will be used in the rtos task.
 */
void motorControl::testMotors() {
#ifdef DEBUG
    motorControl* motorControlInstance = motorControl::_getInstance();
    if (dutyCycleMotor == PWM_MAX_DUTY_CYCLE) {
        incDutyCycleMotor = false;
        motorControlInstance->breakAll();
        motorControlInstance->upDown(false);
    } else if (dutyCycleMotor == PWM_MIN_DUTY_CYCLE) {
        incDutyCycleMotor = true;
        motorControlInstance->breakAll();
        motorControlInstance->upDown(true);
    }
    dutyCycleMotor += incDutyCycleMotor ? 1 : -1;
    bool direction = incDutyCycleMotor ? FORWARD : BACKWARD;

    motorControlInstance->setSpeed(motorControlInstance->_frontLeftMotor, dutyCycleMotor, direction);
    motorControlInstance->setSpeed(motorControlInstance->_frontRightMotor, dutyCycleMotor, direction);
    motorControlInstance->setSpeed(motorControlInstance->_backLeftMotor, dutyCycleMotor, direction);
    motorControlInstance->setSpeed(motorControlInstance->_backRightMotor, dutyCycleMotor, direction);
#endif
}
