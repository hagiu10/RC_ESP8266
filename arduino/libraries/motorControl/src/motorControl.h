#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <commonLibs.h>
#include <pwmSignal.h>
#include <sn74hc595n.h>

// Define variable conform with ESP8266 pin layout
#define D1 5  // D1 is GPIO5
#define D2 4  // D2 is GPIO4
#define D3 0  // D3 is GPIO0
#define D4 2  // D4 is GPIO2
#define D5 14  // D5 is GPIO14
#define D6 12  // D6 is GPIO12
#define D7 13  // D7 is GPIO13
#define D8 15  // D8 is GPIO15

// Define variable conform with schematic layout 
#define OUT4_MFLN D4  // OUT4 - D4 GPIO2 - MFLN -> M = Motor, F = Front motor, L = Left motor, N = Negative
#define OUT3_MFLP D3  // OUT3 - D3 GPIO0 - MFLP -> M = Motor, F = Front motor, L = Left motor, P = Positive
#define OUT2_MFRN D2  // OUT2 - D2 GPIO4 - MFRN -> M = Motor, F = Front motor, R = Right motor, N = Negative
#define OUT1_MFRP D1  // OUT1 - D1 GPIO5 - MFRP -> M = Motor, F = Front motor, R = Right motor, P = Positive

#define OUT8_MBRN D8  // OUT8 - D8 GPIO15 - MBRN -> M = Motor, B = Back motor, R = Right motor, N = Negative
#define OUT7_MBRP D7  // OUT7 - D7 GPIO13 - MBRP -> M = Motor, B = Back motor, R = Right motor, P = Positive
#define OUT6_MBLP D6  // OUT6 - D6 GPIO12 - MBLN -> M = Motor, B = Back motor, L = Left motor, N = Negative
#define OUT5_MBLN D5  // OUT5 - D5 GPIO14 - MBLP -> M = Motor, B = Back motor, L = Left motor, P = Positive

// Define const variable for motor direction
#define FORWARD 1
#define BACKWARD 0

#ifdef DEBUG
extern bool incDutyCycleMotor; // Initialize the global variable
extern uint8_t dutyCycleMotor; // Initialize the global variable
#endif

typedef struct {
  uint8_t pinPositive;
  uint8_t pinNegative;
} motor;

// Function prototypes
class motorControl: public pwmSignal, public sn74hc595n {
  private:
    motor _frontLeftMotor;
    motor _frontRightMotor;
    motor _backLeftMotor;
    motor _backRightMotor;
    static motorControl* _getInstance(void);
  public:
    motorControl();
    static void init(void);
    static void setSpeed(motor motor, uint8_t dutyCycle, bool direction);
    static void breakAll(void);
    static void upDown(bool state);
    static void testMotors(void);
};
#endif // MOTORCONTROL_H