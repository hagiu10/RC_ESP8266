#ifndef CONTROLMOTOR_H
#define CONTROLMOTOR_H

#define DEBUG
// Define const variable conform with ESP8266 pin layout
static const uint8_t D1 = 5;  // D1 is GPIO5
static const uint8_t D2 = 4;  // D2 is GPIO4
static const uint8_t D3 = 0;  // D3 is GPIO0
static const uint8_t D4 = 2;  // D4 is GPIO2
static const uint8_t D5 = 14;  // D5 is GPIO14
static const uint8_t D6 = 12;  // D6 is GPIO12
static const uint8_t D7 = 13;  // D7 is GPIO13
static const uint8_t D8 = 15;  // D8 is GPIO15

// Define const variable conform with schematic layout 
static const uint8_t OUT4_MFLN = D4;  // OUT4 - D4 GPIO2 - MFLN -> M = Motor, F = Front motor, L = Left motor, N = Negative
static const uint8_t OUT3_MFLP = D3;  // OUT3 - D3 GPIO0 - MFLP -> M = Motor, F = Front motor, L = Left motor, P = Positive
static const uint8_t OUT2_MFRN = D2;  // OUT2 - D2 GPIO4 - MFRN -> M = Motor, F = Front motor, R = Right motor, N = Negative
static const uint8_t OUT1_MFRP = D1;  // OUT1 - D1 GPIO5 - MFRP -> M = Motor, F = Front motor, R = Right motor, P = Positive

static const uint8_t OUT8_MBRN = D8;  // OUT8 - D8 GPIO15 - MBRN -> M = Motor, B = Back motor, R = Right motor, N = Negative
static const uint8_t OUT7_MBRP = D7;  // OUT7 - D7 GPIO13 - MBRP -> M = Motor, B = Back motor, R = Right motor, P = Positive
static const uint8_t OUT6_MBLP = D6;  // OUT6 - D6 GPIO12 - MBLN -> M = Motor, B = Back motor, L = Left motor, N = Negative
static const uint8_t OUT5_MBLN = D5;  // OUT5 - D5 GPIO14 - MBLP -> M = Motor, B = Back motor, L = Left motor, P = Positive

// Define const variable for motor direction
static const uint8_t FORWARD = 1;
static const uint8_t BACKWARD = 0;

// Function prototypes
class controlMotor {
  public:
    controlMotor();
    void init(void);
    void frontLeft(uint8_t dutyCycle, bool direction);
    void frontRight(uint8_t dutyCycle, bool direction);
    void backLeft(uint8_t dutyCycle, bool direction);
    void backRight(uint8_t dutyCycle, bool direction);
    void breakAll(void);
};
#endif // CONTROLMOTOR_H