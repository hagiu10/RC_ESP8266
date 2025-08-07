#ifndef SN74HC595N_H
#define SN74HC595N_H

#include <commonLibs.h>

// Define const variable conform with ESP8266 layout
#define D0 16  // D0 is GPIO16
#define RX 3  // RX is GPIO3
#define TX 1  // TX is GPIO1

// Define const variable conform with schematic layout of RC_ESP8266
#define SER TX  // SER is GPIO1. SER is the serial data input for the shift register.
#define RCLK RX // RCLK is GPIO16. RCLK is the storage register clock input. 
                                // Trigger the storage register to save the data.
#define SRCLK D0  // SRCLK is GPIO3. SRCLK is the shift register clock input. 
                                  // Source clock that save data to the shift register.
// Enum to identify index for each attribute in the shift register
// Each attribute is connected to a pin of the SN74HC595N
// Order and name of the attribute in the enum should match the schematic layout
typedef enum {
  Q0_NOT_USED,
  Q1_SPEAKER,
  Q2_LED1,
  Q3_LED2,
  Q4_LED3,
  Q5_MOTOR,
  Q6_LED4,
  Q7_NOT_USED,
  REG_INDEX_COUNT
}regIndex;
// Function prototypes
class sn74hc595n {
  private:
    static uint8_t SN74HC595N_REG;  // Register to store the state of the shift register
    static void _serWriteReg(uint8_t data);
    static sn74hc595n* _getInstance(void);
  public:
    sn74hc595n(); 
    static void init(void);
    static uint8_t getBitRegState(uint8_t indexBit);
    static void setBitRegState(uint8_t indexBit, bool state);
    static void testRegisterSN74HC595N(void);
};
#endif //  SN74HC595N_H