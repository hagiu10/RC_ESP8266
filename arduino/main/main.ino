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
  // voltageMonitor.init();
  webServer::init();
  webServer::loadWebPage();
  webSocket::init();
  rtos::init();
  ledControl::init();
  sn74hc595n::init();
  motorControl::init();
  // rtos::addTask("sn74hc595n", sn74hc595n::testRegisterSN74HC595N, 10e6);
  // rtos::addTask("ledControl", ledControl::testLeds, 10e6);
  // rtos::addTask("pwmSignal", pwmSignal::testDutyCycle, 10e5);
  rtos::addTask("motorControl",motorControl::testMotors, 10e3);
  // rtosDrive.addTask(voltageMonitor.testReadVoltage, 10e6);
  // rtos::addTask("serverLoad", webServer::webServerHandler, 10e4);
  // rtos::addTask("webSocketLoad", webSocket::webSocketHandler, 10e4);
  delay(100);
}

// the loop function runs over and over again forever
void loop() {
  rtos::executeTasks();
}
