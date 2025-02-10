#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <webPage.h>

#define DEBUG

// Function prototypes
class webServer {
  public:
    webServer();
    void init(void);
    void loadWebPage(void);
    void handleClient(void);

  private:
    ESP8266WebServer server;  // Create an instance of the ESP8266WebServer class
};
class webSocket {
  public:
    webSocket();
    void init(void);
    void event(uint8_t num, WStype_t type, uint8_t* payload, size_t length);
    void loop(void);

  private:
    WebSocketsServer socket; // Create an instance of the WebSocketsServer class
};
#endif // WEB_SERVER_H