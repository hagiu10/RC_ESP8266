#include <pwmSignal.h>

#ifdef DEBUG
bool incDutyCycleLed = true; // Initialize the global variable
#endif
listPins pwmSignal::_pinsList[MAX_NR_PINS]; // Initialize the static variable
uint8_t pwmSignal::_nrPins = 0; // Initialize the static variable
uint8_t pwmSignal::_nrInterrupts = 0; // Initialize the static variable
/** Constructor
 */
pwmSignal::pwmSignal() {
// #ifdef DEBUG
//     Serial.printf("pwmSignal::pwmSignal Constructor. [%lu ms]\n", millis());
// #endif
}
/** Initialize the pwmSignal
 */
void pwmSignal::init(void) {
    // Initialize the static variables
    _nrPins = 0;
    _nrInterrupts = 0;
    // Initialize periferal for pwm signal
#ifdef DEBUG
    Serial.printf("pwmSignal::init Initialized. [%lu ms]\n", millis());
#endif
}
/** Task function
 */
void pwmSignal::pwmHandler() {
    // Reset state of all pins to HIGH
    if (_nrInterrupts >= PWM_PERIOD) {
        for (uint8_t i = 0; i < _nrPins; ++i) {
            digitalWrite(_pinsList[i].pin, HIGH);
        }
        _nrInterrupts = 0;
        return;
    }

    // Minimize digitalWrite calls by only toggling pins that need to change
    for (uint8_t i = 0; i < _nrPins; ++i) {
        if (_nrInterrupts == _pinsList[i].dutyCycle) {
            digitalWrite(_pinsList[i].pin, LOW);
        }
    }
    ++_nrInterrupts;
#ifdef DEBUG
    // It is not recommended to use Serial.printf in an interrupt service routine
    // Serial.printf("pwmSignal::pwmHandler Number interupts _nrInterrupts = %d Task executed at [%lu ms]\n",_nrInterrupts, millis());
#endif
}
/** Set duty cycle for a pin
 * @param pin Pin to set duty cycle
 * @param dutyCycle Duty cycle to be set
 */
void pwmSignal::setDutyCycle(uint8_t pin, uint8_t dutyCycle) {
    bool status = false; // Asume pin is not in the list
    if (dutyCycle > PWM_MAX_DUTY_CYCLE) {
        #ifdef DEBUG
            Serial.printf("pwmSignal::setDutyCycle [warning] Duty cycle is above 100%%. [%lu ms]\n", millis());
        #endif
        dutyCycle = PWM_MAX_DUTY_CYCLE;
    }
    if (dutyCycle == PWM_MIN_DUTY_CYCLE || dutyCycle == PWM_MAX_DUTY_CYCLE) {
        _delPin(pin, dutyCycle/PWM_MAX_DUTY_CYCLE);
        return;
    } 
    for (uint8_t i = 0; i < _nrPins; i++) {
        if (_pinsList[i].pin == pin) {
            _pinsList[i].dutyCycle = dutyCycle;
            #ifdef DEBUG
                Serial.printf("pwmSignal::setDutyCycle Pin %d set to %d%%. [%lu ms]\n", pin, dutyCycle, millis());
            #endif
            return;
        }
    }
    _addPin(pin, dutyCycle); 
}
/** Get duty cycle for a pin
 * @param pin Pin to get duty cycle
 */
uint8_t pwmSignal::getDutyCycle(uint8_t pin) {
    for (uint8_t i = 0; i < _nrPins; i++) {
        if (_pinsList[i].pin == pin) {
            #ifdef DEBUG
                Serial.printf("pwmSignal::getDutyCycle Pin %d has duty cycle %d%%. [%lu ms]\n", pin, _pinsList[i].dutyCycle, millis());
            #endif
            return _pinsList[i].dutyCycle;
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
    if (_nrPins >= MAX_NR_PINS) {
        #ifdef DEBUG
            Serial.printf("pwmSignal::_addPin [error] Maximum number of pins exceeded. [%lu ms]\n", millis());
        #endif
        return;
    }
    // Add the new pin to the list   
    _pinsList[_nrPins].pin = pin;
    _pinsList[_nrPins].dutyCycle = dutyCycle;
    ++_nrPins; 
#ifdef DEBUG
    Serial.printf("pwmSignal::_addPin Pin %d added to the list. [%lu ms]\n", pin, millis());
    Serial.printf("pwmSignal::_addPin Pin %d was set to %d%%. [%lu ms]\n", pin, dutyCycle, millis());
#endif
}
/** Delete pin from the list of pins
 * @param pin Pin to be deleted
 */
void pwmSignal::_delPin(uint8_t pin, uint8_t state) {
    bool findPin = false; // Asume pin is not in the list
    for (uint8_t i = 0; i < _nrPins; i++) {
        if (_pinsList[i].pin == pin) {
            findPin = true; // Pin is in the list
            // Shift the pins in the list to delete the pin
            for (uint8_t j = i; j < _nrPins - 1; j++) {
                _pinsList[j] = _pinsList[j + 1];
            }
            _nrPins--;
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
    static uint8_t dutyCycle = getDutyCycle(LED_PIN);
    if (dutyCycle == PWM_MAX_DUTY_CYCLE) {
      incDutyCycleLed = false;
    } else if (dutyCycle == PWM_MIN_DUTY_CYCLE) {
      incDutyCycleLed = true;
    }
    dutyCycle += incDutyCycleLed ? 1 : -1;
    setDutyCycle(LED_PIN, dutyCycle);
#endif
}
