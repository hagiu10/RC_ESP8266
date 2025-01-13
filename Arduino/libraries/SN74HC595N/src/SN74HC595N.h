#ifndef SN74HC595N_H
#define SN74HC595N_H

#define DEBUG

// Define const variable conform with ESP8266 layout
static const uint8_t D0 = 16;  // D0 is GPIO16
static const uint8_t RX = 3;  // RX is GPIO3
static const uint8_t TX = 1;  // TX is GPIO1

// Define const variable conform with schematic layout of RC_ESP8266
static const uint8_t SER = TX;  // SER is GPIO1. SER is the serial data input for the shift register.
static const uint8_t RCLK = RX; // RCLK is GPIO16. RCLK is the storage register clock input. 
                                // Trigger the storage register to save the data.
static const uint8_t SRCLK = D0;  // SRCLK is GPIO3. SRCLK is the shift register clock input. 
                                  // Source clock that save data to the shift register.

// Function prototypes
class sn74hc595n {
  private:
    // Transfer data serial to register of integrated circuit SN74HC595N
    void serWriteReg(uint8_t data);
    public:
    // Enum to identify index for each attribute in the shift register
    enum regIndex {
      Q0_NOT_USED,
      Q1_SPEAKER,
      Q2_LED1,
      Q3_LED2,
      Q4_LED3,
      Q5_MOTOR,
      Q6_LED4,
      Q7_NOT_USED,
      REG_INDEX_COUNT
    };
    // Constructor
    sn74hc595n();
    // Initialize module SN74HC595N 
    void init(void);
    // Set the bit of the regester to high or low using the index bit of the register
    uint8_t getBitRegState(uint8_t indexBit);
    // Get the state of the bit of the register using the index bit of the register
    void setBitRegState(uint8_t indexBit, uint8_t state);
};
class motorUpDown : public sn74hc595n {
  public:
    // Constructor
    motorUpDown();
    // Move the motor up and down
    void start(void);
    // Stop the motor
    void stop(void);
};
class speaker : public sn74hc595n {
  public:
    // Constructor
    speaker();
    // Play the sound
    void start(void);
    // Stop the sound
    void stop(void);
};
class led1 : public sn74hc595n {
  public:
    // Constructor
    led1();
    // Turn on the LED
    void on(void);
    // Turn off the LED
    void off(void);
};
class led2 : public sn74hc595n {
  public:
    // Constructor
    led2();
    // Turn on the LED
    void on(void);
    // Turn off the LED
    void off(void);
};
class led3 : public sn74hc595n {
  public:
    // Constructor
    led3();
    // Turn on the LED
    void on(void);
    // Turn off the LED
    void off(void);
};
class led4 : public sn74hc595n {
  public:
    // Constructor
    led4();
    // Turn on the LED
    void on(void);
    // Turn off the LED
    void off(void);
};
#endif //  SN74HC595N_H