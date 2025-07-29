#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <commonLibs.h>
#include <sn74hc595n.h>

#define NR_OF_LEDS 4
#define LED1 Q2_LED1  // Define the LED pins conform to your hardware setup
#define LED2 Q3_LED2  // Define the LED pins conform to your hardware setup
#define LED3 Q4_LED3  // Define the LED pins conform to your hardware setup
#define LED4 Q6_LED4  // Define the LED pins conform to your hardware setup

#ifdef DEBUG
extern bool stateLeds;  // Global variable declaration for debugging
#endif

// Function prototypes
class ledControl: public sn74hc595n {
  private:
    static ledControl* _getInstance(void);
  public:
    ledControl();
    static void init(void);
    static void setLed(uint8_t led, bool state);
    static void testLeds(void);

};
#endif // LEDCONTROL_H