#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <commonLibs.h>
#include <sn74hc595n.h>

#define NR_OF_LEDS 4
#define LED1 Q2_LED1
#define LED2 Q3_LED2
#define LED3 Q4_LED3
#define LED4 Q6_LED4

#ifdef DEBUG
extern bool stateLeds;  // Global variable declaration for debugging
#endif

// Function prototypes
class ledControl: public sn74hc595n {
  private:
    static ledControl* _getInstance(void);
  public:
    ledControl();
    void init(void);
    void setLed(uint8_t led, uint8_t state);
    static void testLeds(void);

};
#endif // LEDCONTROL_H