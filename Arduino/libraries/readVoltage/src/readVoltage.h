#ifndef READVOLTAGE_H
#define READVOLTAGE_H

#define DEBUG

#define ADC0 0 // Analog pin 0
#define VOLTAGE_PIN ADC0// Analog input from the voltage divider
#define VOLTAGE_DIVIDER 2 // Voltage divider ratio
#define VOLTAGE_REF 3.3  // Maximum voltage reference
// Function prototypes
class readVoltage {
  public:
    readVoltage();
    void init(void);
    float readVoltageBat(void);
};
#endif // READVOLTAGE_H