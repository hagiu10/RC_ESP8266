// Include Arduino.h files in the header file for importing the Arduino library functions.
#include <Arduino.h>
#include <readVoltage.h>

/** Constructor
 */
readVoltage::readVoltage() {
}
/** Initialize the voltage sensor
 */
void readVoltage::init(void) {
    analogRead(VOLTAGE_PIN);
}
/** Read the voltage from the sensor
 */
float readVoltage::readVoltageBat(void) {
    int batValue = analogRead(VOLTAGE_PIN);
    float voltage = batValue * (VOLTAGE_REF / 1023.0);
  
#ifdef DEBUG
    Serial.print("Battery voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
#endif
    return voltage;
}