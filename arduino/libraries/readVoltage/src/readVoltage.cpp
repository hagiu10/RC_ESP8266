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
    int batValue = analogRead(VOLTAGE_PIN);
    float voltage = batValue * (VOLTAGE_REF / 1023.0);
  
#ifdef DEBUG
    Serial.printf("readVoltage::readVoltageBat voltage:%.3f[V], batValue: %d[int] [%lu ms]\n", voltage, batValue, millis());
#endif
    return voltage;
}
/** Test function to read the voltage
 * This function is used to test the readVoltage class.
 */
void readVoltage::testReadVoltage() {
    float voltage = readVoltageBat() * VOLTAGE_DIVIDER;
    Serial.printf("readVoltage::testReadVoltage Test readVoltage: %.3f[V]. [%lu ms]\n", voltage, millis());
}