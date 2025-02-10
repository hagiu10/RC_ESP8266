// Include Arduino.h files in the header file for importing the Arduino library functions.
#include <Arduino.h>
#include "webServer.h"

/** Constructor
 */
webServer::webServer(): server(80) {
    // server = new AsyncWebServer(80);  // Port 80 is the default port for HTTP
}
/** Initialize the web server
 */
void webServer::init(void) {
    boolean result =  WiFi.softAP("ESP8266", "123456789");
#ifdef DEBUG
    if (result) {
        Serial.print("\nWiFi soft access point is running\n");
    } else {
        Serial.print("WiFi soft access point failed\n");
    }
#endif
    IPAddress local_IP(192, 168, 1, 1);  // Set your desired IP address
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    result = WiFi.softAPConfig(local_IP, gateway, subnet);
#ifdef DEBUG
    if (result) {
        Serial.println("AP Config Success");
    } else {
        Serial.println("AP Config Failed");
    }
#endif
}
/** Load the web page
 */
void webServer::loadWebPage(void) {
    // Load the web page
    server.on("/", HTTP_GET, [this]() {
        server.send_P(200, "text/html", webPage_html);
    });
    server.begin(); 
#ifdef DEBUG
    Serial.print("Web server is running\n");
#endif
}
/** Handle the client request
 */
void webServer::handleClient(void) {
    server.handleClient();
}
/** Constructor
 */
webSocket::webSocket(): socket(81) {
    // socket = new WebSocketsServer(81);  // Port 81 is the default port for WebSockets
}
/** Initialize the web socket
 */
void webSocket::init(void) {
    // Initialize WebSocket server
    socket.begin();
    socket.onEvent([this](uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
        this->event(num, type, payload, length);
    });
}
/** Handle the WebSocket event
 */
void webSocket::event(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    String message = " ";
    switch (type) {
        case WStype_DISCONNECTED:
          message = "Disconnected!";
          break;
        case WStype_CONNECTED:
          message = "Connected!";
          break;
        case WStype_TEXT:
          message = "Received: ";
          String text = String((char*)payload);
          String echoMessage = "Receive: " + String((char*)payload);
          socket.sendTXT(num, echoMessage);
          break;
      }
#ifdef DEBUG
    Serial.print("WebSocket event: ");  
    Serial.printf("[%s] %s %s \n", num, message, String((char*)payload));
#endif
}
/** Handle the WebSocket event
 */
void webSocket::loop(void) {
    socket.loop();
}