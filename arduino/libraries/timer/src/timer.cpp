#include <timer.h>

/** Constructor
 */
timer::timer() {
    _frequency = 0;
    _timerCount = 0;
    _callback = NULL;
#ifdef DEBUG
    Serial.printf("ESP8266TimerInterrupt: Constructor\n");
#endif
}

/** Initialize the timer
 */
void timer::init(void) {
    timer* timerInstance = timer::_getInstance();
    float minFreq = (float) TIM_CLOCK_FREQ / MAX_COUNT;
    timerInstance->_frequency = minFreq;
    timerInstance->_timerCount = 800;//(uint32_t) (TIM_CLOCK_FREQ / _frequency);
    timer1_write(timerInstance->_timerCount);
    // Set up the timer interrupt and enable the timer
    timer1_enable(TIM_DIV, TIM_EDGE, TIM_LOOP);
#ifdef DEBUG
    Serial.printf("timer::init Timer initialized with frequency %f Hz and timer count %d. [%lu ms]\n", timerInstance->_frequency, timerInstance->_timerCount, millis());
    // if (timerInstance->_frequency < minFreq) {
    //     Serial.printf("ESP8266TimerInterrupt: Timer frequency (%f) is below minimum frequency (%f)\n", _frequency, minFreq);
    // }
    Serial.printf("timer::init Timer count set to %d. [%lu ms]\n", timerInstance->_timerCount, millis());
    if (timerInstance->_timerCount > MAX_COUNT) {
        Serial.printf("timer::init [error] Timer count exceeds maximum count of %d. [%lu ms]\n", MAX_COUNT, millis());
    }
#endif
}

/** Interrupt function
 * @param callback Callback function
 */
void timer::interrupt(timer_callback callback) {
    timer* timerInstance = timer::_getInstance();
    // Set the callback function
    if (callback == NULL) {
        #ifdef DEBUG
            Serial.printf("timer::interrupt [error] Callback function is NULL %p. [%lu ms]\n", callback, millis());
        #endif
        return;
    }
    timerInstance->_callback = callback;
    // Attach the interrupt
    timer1_attachInterrupt(timerInstance->_callback);
#ifdef DEBUG
    Serial.printf("timer::interrupt Callback function set to %p. [%lu ms]\n", timerInstance->_callback, millis());
#endif
}
/** Get the instance of the timer
 */
timer* timer::_getInstance(void) {
    // Create a static instance of the timer class
    static timer timerInstance;
    // Return the instance
    return &timerInstance;
}