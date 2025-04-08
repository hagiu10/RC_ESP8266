#include <readVoltage.h>

/** Constructor
 */
readVoltage::readVoltage() {
}
/** Initialize the analog digital converter (ADC)
 */
void readVoltage::init(void) {
    analogRead(VOLTAGE_PIN);
#ifdef DEBUG
    Serial.printf("readVoltage::init Initialized ADC. [%lu ms]\n", millis());
#endif
}
/** Read the voltage from the sensor
 */
float readVoltage::readVoltageBat(void) {
    uint8_t batValue = analogRead(VOLTAGE_PIN);
    float_t voltage = batValue * (VOLTAGE_REF / 1023.0);
  
#ifdef DEBUG
    Serial.printf("readVoltage::readVoltageBat Battery voltage:%.3f [%lu ms]\n", voltage, millis());
#endif
    return voltage;
}
/** Test function to read the voltage
 * This function is used to test the readVoltage class.
 */
void readVoltage::testReadVoltage() {
    readVoltage voltageMonitor;
    float voltage = voltageMonitor.readVoltageBat();
    Serial.printf("readVoltage::testReadVoltage Test readVoltage: %.3f V\n", voltage);
}