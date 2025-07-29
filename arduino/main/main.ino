#include <commonLibs.h>
#include <motorControl.h>
#include <readVoltage.h>
#include <webServer.h>
#include <webSocketsNew.h>
#include <rtos.h>
#include <ledControl.h>
#include <sn74hc595n.h>

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
  // motorsDrive.init();
  // multiplexPins.init();
  // voltageMonitor.init();
  webServer::init();
  webServer::loadWebPage();
  webSocket::init();
  rtos::init();
  ledControl::init();
  sn74hc595n::init();
  //rtos::addTask("sn74hc595n", sn74hc595n::testRegisterSN74HC595N, 10e6);
  rtos::addTask("ledControl", ledControl::testLeds, 10e6);
  // rtos::addTask("blinkLed", pwmSignal::testDutyCycle, 100000);
  // rtosDrive.addTask(motorsDrive.testMotors, 200000);
  // rtosDrive.addTask(voltageMonitor.testReadVoltage, 1000000);
  // rtos::addTask("serverLoad", webServer::webServerHandler, 10000);
  // rtos::addTask("webSocketLoad", webSocket::webSocketHandler, 10000);
  delay(100);
}

// the loop function runs over and over again forever
void loop() {
  rtos::executeTasks();
}
