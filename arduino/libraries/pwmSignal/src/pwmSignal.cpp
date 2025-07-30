#include <pwmSignal.h>

#ifdef DEBUG
bool incDutyCycleLed = true; // Initialize the global variable
#endif

/** Constructor
 */
pwmSignal::pwmSignal() {
    _nrPins = 0;
    _nrInterrupts = 0;
#ifdef DEBUG
    Serial.printf("pwmSignal::pwmSignal Constructor. [%lu ms]\n", millis());
#endif
}
/** Initialize the pwmSignal
 */
void pwmSignal::init(void) {
    // Initialize periferal for pwm signal
#ifdef DEBUG
    Serial.printf("pwmSignal::init Initialized. [%lu ms]\n", millis());
#endif
}
/** Task function
 */
void pwmSignal::pwmHandler() {
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    if (pwmInstance == nullptr) {
        #ifdef DEBUG
            Serial.printf("pwmSignal::pwmHandler [error] pwmInstance is NULL. [%lu ms]\n", millis());
        #endif
        return;
    }
    // Reset state of all pins to HIGH
    if (pwmInstance->_nrInterrupts >= PWM_PERIOD) {
        for (uint8_t i = 0; i < pwmInstance->_nrPins; i++) {
            digitalWrite(pwmInstance->_pins[i].pin, HIGH);
        }
        pwmInstance->_nrInterrupts = 0; 
        return;
    }
    for (uint8_t i = 0; i < pwmInstance->_nrPins; i++) {
        if (pwmInstance->_nrInterrupts >= pwmInstance->_pins[i].dutyCycle) {
            digitalWrite(pwmInstance->_pins[i].pin, LOW);
        }
    }
    pwmInstance->_nrInterrupts++;
#ifdef DEBUG
    // It is not recommended to use Serial.printf in an interrupt service routine
    // Serial.printf("pwmSignal::pwmHandler Number interupts _nrInterrupts = %d Task executed at [%lu ms]\n",pwmInstance->_nrInterrupts, millis());
#endif
}
/** Set duty cycle for a pin
 * @param pin Pin to set duty cycle
 * @param dutyCycle Duty cycle to be set
 */
void pwmSignal::setDutyCycle(uint8_t pin, uint8_t dutyCycle) {
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    bool status = false; // Asume pin is not in the list
    if (dutyCycle > PWM_MAX_DUTY_CYCLE) {
        #ifdef DEBUG
            Serial.printf("pwmSignal::setDutyCycle [warning] Duty cycle is above 100%%. [%lu ms]\n", millis());
        #endif
        dutyCycle = PWM_MAX_DUTY_CYCLE;
    }
    if (dutyCycle == PWM_MIN_DUTY_CYCLE || dutyCycle == PWM_MAX_DUTY_CYCLE) {
        pwmInstance->_delPin(pin, dutyCycle/PWM_MAX_DUTY_CYCLE);
        return;
    } 
    for (uint8_t i = 0; i < pwmInstance->_nrPins; i++) {
        if (pwmInstance->_pins[i].pin == pin) {
            pwmInstance->_pins[i].dutyCycle = dutyCycle;
            #ifdef DEBUG
                Serial.printf("pwmSignal::setDutyCycle Pin %d set to %d%%. [%lu ms]\n", pin, dutyCycle, millis());
            #endif
            return;
        }
    }
    pwmInstance->_addPin(pin, dutyCycle); 
}
/** Get duty cycle for a pin
 * @param pin Pin to get duty cycle
 */
uint8_t pwmSignal::getDutyCycle(uint8_t pin) {
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    for (uint8_t i = 0; i < pwmInstance->_nrPins; i++) {
        if (pwmInstance->_pins[i].pin == pin) {
            #ifdef DEBUG
                Serial.printf("pwmSignal::getDutyCycle Pin %d has duty cycle %d%%. [%lu ms]\n", pin, pwmInstance->_pins[i].dutyCycle, millis());
            #endif
            return pwmInstance->_pins[i].dutyCycle;
        }
    }
#ifdef DEBUG
    Serial.printf("pwmSignal::getDutyCycle Pin %d not found in the list. [%lu ms]\n", pin, millis());
#endif
    return 0; 
}
/** Add pin to the list of pins
 * @param pin Pin to be added
 * @param dutyCycle Duty cycle to be set
 */
void pwmSignal::_addPin(uint8_t pin, uint8_t dutyCycle) {
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    if (pwmInstance->_nrPins > MAX_NR_PINS) {
        #ifdef DEBUG
            Serial.printf("pwmSignal::_addPin [error] Maximum number of pins exceeded. [%lu ms]\n", millis());
        #endif
        return;
    }
    // Add the new pin to the list
    pwmInstance->_pins[_nrPins].pin = pin;
    pwmInstance->_pins[_nrPins].dutyCycle = dutyCycle;
    pwmInstance->_nrPins++; 
#ifdef DEBUG
    Serial.printf("pwmSignal::_addPin Pin %d added to list. [%lu ms]\n", pin, millis());
    Serial.printf("pwmSignal::setDutyCycle Pin %d set to %d%%. [%lu ms]\n", pin, dutyCycle, millis());
#endif
}
/** Delete pin from the list of pins
 * @param pin Pin to be deleted
 */
void pwmSignal::_delPin(uint8_t pin, uint8_t state) {
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    bool findPin = false; // Asume pin is not in the list
    for (uint8_t i = 0; i < pwmInstance->_nrPins; i++) {
        if (pwmInstance->_pins[i].pin == pin) {
            findPin = true; // Pin is in the list
            // Shift the pins in the list to delete the pin
            for (uint8_t j = i; j < pwmInstance->_nrPins - 1; j++) {
                pwmInstance->_pins[j] = _pins[j + 1];
            }
            pwmInstance->_nrPins--;
            // Set the state of the pin
            digitalWrite(pin, state);
            break;
        }
    }
#ifdef DEBUG
    if (!findPin) {
        Serial.printf("pwmSignal::_delPin Pin %d not found in the list. [%lu ms]\n", pin, millis());
    }else {
        Serial.printf("pwmSignal::_delPin Pin %d deleted from the list. [%lu ms]\n", pin, millis());
        Serial.printf("pwmSignal::_delPin Digital write pin %d with state %d. [%lu ms]\n", pin, state, millis());
    }
#endif
}
/* Get the instance of the pwmSignal
 */
pwmSignal* pwmSignal::_getInstance(void) {
    static pwmSignal instance;
    return &instance;
}
/**Test duty cycle
 * This function is used to test the duty cycle of the LED
 * For the LED, the duty cycle is increased from 0 to 100% and then decreased from 100 to 0%
 * The duty cycle is increased or decreased by 1% at a time
 * Time period for increasing or decreasing theduty cycle is given by run time of the task
 * This function is called by the RTOS to test the duty cycle of the LED
 */
void pwmSignal::testDutyCycle() {
#ifdef DEBUG
    pwmSignal* pwmInstance = pwmSignal::_getInstance();
    static uint8_t dutyCycle = pwmInstance->getDutyCycle(LED_PIN);
    if (dutyCycle == PWM_MAX_DUTY_CYCLE) {
      incDutyCycleLed = false;
    } else if (dutyCycle == PWM_MIN_DUTY_CYCLE) {
      incDutyCycleLed = true;
    }
    dutyCycle += incDutyCycleLed ? 1 : -1;
    pwmInstance->setDutyCycle(LED_PIN, dutyCycle);
#endif
}
