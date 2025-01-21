// Include Arduino.h files in the header file for importing the Arduino library functions.
#include <Arduino.h>
#include <SN74HC595N.h>

// Define global variables for the shift register
uint8_t SN74HC595N_REG = 0x00; // Initialize the shift register state to 0x00

/** Constructor  
 * This is the constructor for the sn74hc595n class.
 */
sn74hc595n::sn74hc595n() {
    // Constructor implementation
}
/** Initialize pins of esp8266
 * This function initializes the pins to controll the shift register of the integrated circuit SN74HC595N.
 */
void sn74hc595n::init(void) {
    // Initialize the pins
    pinMode(D0, OUTPUT);  // sets the pin D0 as output
    pinMode(RX, OUTPUT);  // sets the pin RX as output
    pinMode(TX, OUTPUT);  // sets the pin TX as output
    serWriteReg(SN74HC595N_REG);  // clear the shift register, set all the pins to low
#ifdef DEBUG
    // Serial port for debugging purposes
    Serial.begin(115200);
#endif
}
/** Transfer data serial to register of integrated circuit SN74HC595N
 * This function writes data to the register.
 * @param data The data to be write to the register.
 */
void sn74hc595n::serWriteReg(uint8_t data) {
#ifdef DEBUG
    delay(100);  // delay for 100ms to allow the serial UART to finish sending data
    pinMode(RX, OUTPUT);  // sets the pin RX as output
    pinMode(TX, OUTPUT);  // sets the pin TX as output
#endif
    // Code to shift data to the shift register
    digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
    digitalWrite(SER, LOW);  // set the SER pin to low
    digitalWrite(RCLK, LOW);  // start sending data to the shift register
    for(int i = 0; i < 8; i++) {
        digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
        digitalWrite(SER, (data >> i) & 0x01);  // shift data to the SER pin
        digitalWrite(SRCLK, HIGH);  // set the SRCLK pin to high
    }
    digitalWrite(SRCLK, LOW);  // set the SRCLK pin to low
    digitalWrite(SER, LOW);  // set the SER pin to low
    digitalWrite(RCLK, HIGH);  // save the data to the storage register
#ifdef DEBUG
    // Serial port for debugging purposes
    Serial.begin(115200);
    Serial.printf("Data shifted to register %d: \n", data);
#endif
}
/** Get the state of the bit of the register
 * This function gets the state of the bit of the register using the index of the bit register.
 * @param indexBit The index of the bit register.
 * @return The state of the bit of the register.
 */
uint8_t sn74hc595n::getBitRegState(uint8_t indexBit) {
#ifdef DEBUG
    Serial.printf("Get register state of index %d : %d\n", indexBit, (SN74HC595N_REG >> indexBit) & 0x01);
#endif
    // Get the state of the pin of the register
    return (SN74HC595N_REG >> indexBit) & 0x01;
}
/** Set the bit of the register to high or low
 * This function sets the bit of the register to high or low using the index of the register.
 * @param indexBit The index of the register.
 * @param state The state of the bit of the register.
 */
void sn74hc595n::setBitRegState(uint8_t indexBit, uint8_t state) {
    // Set the pin of the register to high or low
    if(state == HIGH) {
        SN74HC595N_REG |= (1 << indexBit);
    } else {
        SN74HC595N_REG &= ~(1 << indexBit);
    }
    serWriteReg(SN74HC595N_REG);  // shift the data to the shift register
#ifdef DEBUG
    Serial.println("Set register state");
#endif
}
/** Constructor  
 * This is the constructor for the motorUpDown class.
 */
motorUpDown::motorUpDown() {
    // Constructor implementation
}
/** Move the motor up and down
 * This function moves the motor up and down.
 */
void motorUpDown::start(void) {
    // Move the motor up and down
    setBitRegState(Q5_MOTOR, HIGH);  // set the motor pin to high
#ifdef DEBUG
    Serial.println("Motor up and down started");
#endif
}
/** Stop the motor
 * This function stops the motor.
 */
void motorUpDown::stop(void) {
    // Stop the motor
    setBitRegState(Q5_MOTOR, LOW);  // set the motor pin to low
#ifdef DEBUG
    Serial.println("Motor up and down stopped");
#endif
}
/** Constructor  
 * This is the constructor for the speaker class.
 */
speaker::speaker() {
    // Constructor implementation
}
/** Play the sound
 * This function plays the sound.
 */
void speaker::start(void) {
    // Play the sound
    setBitRegState(Q1_SPEAKER, HIGH);  // set the speaker pin to high
#ifdef DEBUG
    Serial.println("Sound started");
#endif
}
/** Stop the sound
 * This function stops the sound.
 */
void speaker::stop(void) {
    // Stop the sound
    setBitRegState(Q1_SPEAKER, LOW);  // set the speaker pin to low
#ifdef DEBUG
    Serial.println("Sound stopped");
#endif
}
/** Constructor  
 * This is the constructor for the led1 class.
 */
led1::led1() {
    // Constructor implementation
}
/** Turn on the LED
 * This function turns on the LED.
 */
void led1::on(void) {
    // Turn on the LED
    setBitRegState(Q2_LED1, HIGH);  // set the LED pin to high
#ifdef DEBUG
    Serial.println("LED1 on");
#endif
}
/** Turn off the LED
 * This function turns off the LED.
 */
void led1::off(void) {
    // Turn off the LED
    setBitRegState(Q2_LED1, LOW);  // set the LED pin to low
#ifdef DEBUG    
    Serial.println("LED1 off");
#endif
}
/** Constructor  
 * This is the constructor for the led2 class.
 */
led2::led2() {
    // Constructor implementation
}
/** Turn on the LED
 * This function turns on the LED.
 */
void led2::on(void) {
    // Turn on the LED
    setBitRegState(Q3_LED2, HIGH);  // set the LED pin to high
#ifdef DEBUG
    Serial.println("LED2 on");
#endif
}
/** Turn off the LED
 * This function turns off the LED.
 */
void led2::off(void) {
    // Turn off the LED
    setBitRegState(Q3_LED2, LOW);  // set the LED pin to low
#ifdef DEBUG
    Serial.println("LED2 off");
#endif
}
/** Constructor  
 * This is the constructor for the led3 class.
 */
led3::led3() {
    // Constructor implementation
}
/** Turn on the LED
 * This function turns on the LED.
 */
void led3::on(void) {
    // Turn on the LED
    setBitRegState(Q4_LED3, HIGH);  // set the LED pin to high
#ifdef DEBUG
    Serial.println("LED3 on");
#endif
}
/** Turn off the LED
 * This function turns off the LED.
 */
void led3::off(void) {
    // Turn off the LED
    setBitRegState(Q4_LED3, LOW);  // set the LED pin to low
#ifdef DEBUG
    Serial.println("LED3 off");
#endif    
}
/** Constructor  
 * This is the constructor for the led4 class.
 */
led4::led4() {
    // Constructor implementation
}
/** Turn on the LED
 * This function turns on the LED.
 */
void led4::on(void) {
    // Turn on the LED
    setBitRegState(Q6_LED4, HIGH);  // set the LED pin to high
#ifdef DEBUG
    Serial.println("LED4 on");
#endif
}
/** Turn off the LED
 * This function turns off the LED.
 */
void led4::off(void) {
    // Turn off the LED
    setBitRegState(Q6_LED4, LOW);  // set the LED pin to low
#ifdef DEBUG
    Serial.println("LED4 off");
#endif
}