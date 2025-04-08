#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <commonLibs.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "../utils/webPage.h"


extern ESP8266WebServer server;  // Create an instance of the ESP8266WebServer class

// Function prototypes
class webServer {
  private:
    //ESP8266WebServer server;  // Create an instance of the ESP8266WebServer class
    static webServer* _getInstance(void);
  public:
    webServer();
    void init(void);
    void loadWebPage(void);
    static void webServerHandler(void);
};
#endif // WEB_SERVER_H
