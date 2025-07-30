#include <ledControl.h>

#ifdef DEBUG
bool stateLeds = off; // Initialize the global variable
#endif
/** Constructor
 */
ledControl::ledControl() {
    // Constructor implementation
}
/** Init function
 * This function initializes the pins to control the shift register of the integrated circuit SN74HC595N.
 */
void ledControl::init(void) {
    // Initialize the shift register
    sn74hc595n::init();
#ifdef DEBUG
    Serial.printf("ledControl::init Initialized all pins for leds control. [%lu ms]\n", millis());
#endif
}
/** Set the state of the led
 * This function sets the state of the led.
 * @param led The led to be controlled
 * @param state The state of the led. 0 - off, 1 - on
 */
void ledControl::setLed(uint8_t led, bool state) {
    // Code to control the led
    setBitRegState(led, state);
#ifdef DEBUG
    Serial.printf("ledControl::setLed Set led %d to state %d. [%lu ms]\n", led, state, millis());
#endif
}
/** Get instance of the ledControl
 * This function returns the instance of the ledControl class.
 * @return The instance of the ledControl class
 */
ledControl* ledControl::_getInstance(void) {
    static ledControl instance;
    return &instance;
}
/** Test leds using shift register
 * This function tests leds using shift register.
 */
void ledControl::testLeds() {
#ifdef DEBUG
    // testRegisterSN74HC595N();  // Test the shift register
    ledControl* ledControlInstance = ledControl::_getInstance();
    stateLeds = !stateLeds;
    ledControlInstance->setLed(LED1, stateLeds);
    ledControlInstance->setLed(LED2, stateLeds);
    ledControlInstance->setLed(LED3, stateLeds);
    ledControlInstance->setLed(LED4, stateLeds);
    Serial.printf("ledControl::testLeds Test leds and change state in %d. [%lu ms]\n",stateLeds, millis());
#endif
}
