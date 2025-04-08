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
    float minFreq = (float) TIM_CLOCK_FREQ / MAX_COUNT;
    _frequency = minFreq;
    _timerCount = 800;//(uint32_t) (TIM_CLOCK_FREQ / _frequency);
    timer1_write(_timerCount);
    // Set up the timer interrupt and enable the timer
    timer1_enable(TIM_DIV, TIM_EDGE, TIM_LOOP);
#ifdef DEBUG
    Serial.printf("ESP8266TimerInterrupt: Timer _frequency = %f\n", _frequency);
    // if (_frequency < minFreq) {
    //     Serial.printf("ESP8266TimerInterrupt: Timer frequency (%f) is below minimum frequency (%f)\n", _frequency, minFreq);
    // }
    Serial.printf("ESP8266TimerInterrupt: _timerCount = %d\n", _timerCount);
    if (_timerCount > MAX_COUNT) {
        Serial.printf("ESP8266TimerInterrupt: _timerCount (%d) is above maximum count (%d)\n", _timerCount, MAX_COUNT);
    }
#endif
}

/** Interrupt function
 * @param callback Callback function
 */
void timer::interrupt(timer_callback callback) {
    // Set the callback function
    if (callback == NULL) {
        #ifdef DEBUG
            Serial.printf("ESP8266TimerInterrupt: [error] Callback function is NULL\n");
        #endif
        return;
    }
    _callback = callback;
    // Attach the interrupt
    timer1_attachInterrupt(_callback);
#ifdef DEBUG
    Serial.printf("ESP8266TimerInterrupt: Interrupt attached\n");
#endif
}