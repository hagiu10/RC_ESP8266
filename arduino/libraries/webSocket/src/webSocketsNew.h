#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H

// I used webSocketsNew.h and webSocketsNew.cpp to avoid name conflicts with the WebSockets library

#include <commonLibs.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>


extern WebSocketsServer socket; // Create an instance of the WebSocketsServer class

// Function prototypes
class webSocket {
  private:
    // WebSocketsServer socket; // Create an instance of the WebSocketsServer class
    static webSocket* _getInstance(void);
    void _event(uint8_t num, WStype_t type, uint8_t* payload, size_t length);
    String _executeCliCommand(String command);
  public:
    webSocket();
    void init(void);
    static void webSocketHandler(void);
};
#endif // WEB_SOCKET_H
