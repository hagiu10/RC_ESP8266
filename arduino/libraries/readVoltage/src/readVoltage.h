#ifndef READVOLTAGE_H
#define READVOLTAGE_H

#include <commonLibs.h>

#define ADC0 0 // Analog pin 0
#define VOLTAGE_PIN ADC0// Analog input from the voltage divider
#define VOLTAGE_DIVIDER 3.0 // Voltage divider ratio
#define VOLTAGE_REF 3.3  // Maximum voltage reference

// Function prototypes
class readVoltage {
  public:
    readVoltage();
    static void init(void);
    static float readVoltageBat(void);
    static void testReadVoltage();
};
#endif // READVOLTAGE_H
