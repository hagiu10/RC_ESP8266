#ifndef PWMSIGNAL_H
#define PWMSIGNAL_H

#include <commonLibs.h>

#define MAX_NR_PINS 8 // Maximum number of pins
#define PWM_PERIOD 100 // PWM period in number of interrupts. 100 interrupts = 1 ms for 10 us interrupt period
#define PWM_MAX_DUTY_CYCLE 100 // Maximum duty cycle
#define PWM_MIN_DUTY_CYCLE 0 // Minimum duty cycle
#define LED_PIN 2

#ifdef DEBUG
extern bool incDutyCycleLed; // Initialize the global variable
#endif

typedef struct{
  uint8_t pin;
  uint8_t dutyCycle;
}listPins;

// Function prototypes
class pwmSignal {
  private:
    listPins _pins[MAX_NR_PINS];
    uint8_t _nrPins;
    uint8_t _nrInterrupts;
    void _addPin(uint8_t pin, uint8_t dutyCycle);
    void _delPin(uint8_t pin, uint8_t state);
    static pwmSignal* _getInstance(void);
  public:
    pwmSignal();
    static void init(void);
    static void setDutyCycle(uint8_t pin, uint8_t dutyCycle);
    static uint8_t getDutyCycle(uint8_t pin);
    static void pwmHandler();
    static void testDutyCycle(); 
};
#endif // PWMSIGNAL_H