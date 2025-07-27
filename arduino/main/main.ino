#include <commonLibs.h>
#include <motorControl.h>
#include <readVoltage.h>
#include <webServer.h>
#include <webSocketsNew.h>
#include <rtos.h>

motorControl motorsDrive; // create an instance of the controlMotor class
sn74hc595n multiplexPins; // create an instance of the sn74hc595n class
readVoltage voltageMonitor; // create an instance of the readVoltage class
webServer serverLoad; // create an instance of the webServer class
webSocket webSocketLoad; // create an instance of the webSocket class
pwmSignal pwmDrive; // create an instance of the pwmSignal class

// the setup function runs once when you press reset or power the board
void setup() {
#ifdef DEBUG
  // Serial port for debugging purposes
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Starting...\n");
#endif
  motorsDrive.init();
  multiplexPins.init();
  voltageMonitor.init();
  serverLoad.init();
  serverLoad.loadWebPage();
  webSocketLoad.init();
  rtos::init();
  rtos::addTask("blinkLed", pwmSignal::testDutyCycle, 100000);
  rtos::removeTask("blinkLed");
  rtos::addTask("blinkLed", pwmSignal::testDutyCycle, 100000);
  // rtosDrive.addTask(motorsDrive.testMotors, 200000);
  // rtosDrive.addTask(voltageMonitor.testReadVoltage, 1000000);
  // rtosDrive.addTask(serverLoad.webServerHandler, 10000);
  // rtosDrive.addTask(webSocketLoad.webSocketHandler, 10000);
  delay(100);
}

// the loop function runs over and over again forever
void loop() {
  rtos::executeTasks();
}
