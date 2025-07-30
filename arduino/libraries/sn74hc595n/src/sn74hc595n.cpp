#include <sn74hc595n.h>

uint8_t sn74hc595n::SN74HC595N_REG = 0x00;

/** Constructor  
 * This is the constructor for the sn74hc595n class.
 */
sn74hc595n::sn74hc595n() {
    // Constructor implementation
    // SN74HC595N_REG = 0x00;  // Initialize the register to 0x00
}
/** Initialize pins of esp8266
 * This function initializes the pins to controll the shift register of the integrated circuit SN74HC595N.
 */
void sn74hc595n::init(void) {
    SN74HC595N_REG = 0x00;  // Initialize the register to 0x00
    // Initialize the pins
    pinMode(D0, OUTPUT);  // sets the pin D0 as output
    pinMode(RX, OUTPUT);  // sets the pin RX as output
    pinMode(TX, OUTPUT);  // sets the pin TX as output
    _serWriteReg(SN74HC595N_REG);  // write the data to the register
#ifdef DEBUG
    // Serial port for debugging purposes
    Serial.begin(115200);
    Serial.printf("sn74hc595n::init Initialized. [%lu ms]\n", millis());
#endif
}
/** Transfer data serial to register of integrated circuit SN74HC595N
 * This function writes data to the register.
 * @param data The data to be write to the register.
 */
void sn74hc595n::_serWriteReg(uint8_t data) {
#ifdef DEBUG
    // Wait until all data is sent to the serial port
    while (Serial.availableForWrite() < UART_TX_FIFO_SIZE) {
        // Wait until there is enough space in the buffer to send data
        ets_delay_us(100);  // Small delay to avoid busy-waiting
    }
#endif
    pinMode(RX, OUTPUT);  // sets the pin RX as output
    pinMode(TX, OUTPUT);  // sets the pin TX as output
    // Code to shift data to the shift register
    digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
    digitalWrite(SER, LOW);  // set the SER pin to low
    digitalWrite(RCLK, LOW);  // start sending data to the shift register
    for(int i = 7; i >= 0; i--) {
        digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
        digitalWrite(SER, (data >> i) & 0x01);  // shift data to the SER pin (MSB first)
        digitalWrite(SRCLK, HIGH);  // set the SRCLK pin to high
    }
    digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
    digitalWrite(SER, LOW);  // set the SER pin to low
    digitalWrite(RCLK, HIGH);  // save the data to the storage register
#ifdef DEBUG
   Serial.begin(115200);
   Serial.printf("\nsn74hc595n::_serWriteReg Data write to register: %d [%lu ms]\n", data, millis());
#endif
}
/** Get the state of the bit of the register
 * This function gets the state of the bit of the register using the index of the bit register.
 * @param indexBit The index of the bit register.
 * @return The state of the bit of the register.
 */
uint8_t sn74hc595n::getBitRegState(uint8_t indexBit) {
    uint8_t regState = (SN74HC595N_REG >> indexBit) & 0x01;
#ifdef DEBUG
    Serial.printf("sn74hc595n::getBitRegState Get register state of index %d : %d [%lu ms]\n", indexBit, regState, millis());
#endif
    // Get the state of the pin of the register
    return regState;
}
/** Set the bit of the register to high or low
 * This function sets the bit of the register to high or low using the index of the register.
 * @param indexBit The index of the register.
 * @param state The state of the bit of the register.
 */
void sn74hc595n::setBitRegState(uint8_t indexBit, bool state) {
    // Set the pin of the register to high or low
    if(state == HIGH) {
        SN74HC595N_REG |= (1 << indexBit);
    } else {
        SN74HC595N_REG &= ~(1 << indexBit);
    }
    _serWriteReg(SN74HC595N_REG);  // shift the data to the shift register
#ifdef DEBUG
    Serial.printf("sn74hc595n::setBitRegState Set register state of index indexBit : %d, state : %d [%lu ms]\n", indexBit, state, millis());
#endif
}
/** Get instance 
 * This function returns the instance of the sn74hc595n class.
 * @return The instance of the sn74hc595n class
 */
sn74hc595n* sn74hc595n::_getInstance(void) {
    static sn74hc595n instance;
    return &instance;
}
/** Verify the functionality of controlling SN74HC595N
 * This function verifies the functionality of controlling SN74HC595N by toggling all bits of the register to 1 and 0 alternately.
 */
void sn74hc595n::testRegisterSN74HC595N() {
    sn74hc595n* sn74hc595nInstance = _getInstance();  // create an instance of the sn74hc595n class
    // Toggle all bits to 1 and write to the register
    uint8_t regValue = SN74HC595N_REG==0x00? 0xFF : 0x00;  // Toggle the register state
    // Set each bit using setBitRegState for all 8 pins
    for (uint8_t i = 0; i < 8; ++i) {
        bool bitState = (regValue >> i) & 0x01;
        sn74hc595nInstance->setBitRegState(i, bitState);
    }
    // Use next code just in case you want to see segnals on osciloscope
    // uint8_t regValue = 0x5C;
    // _serWriteReg(regValue);  // write the data to the register
#ifdef DEBUG
   Serial.printf("sn74hc595n::testRegisterSN74HC595N Test register state: %d [%lu ms]\n", SN74HC595N_REG, millis());
#endif
}
