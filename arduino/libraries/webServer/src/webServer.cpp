#include <webServer.h>

ESP8266WebServer server = ESP8266WebServer(80);  // Create an instance of the ESP8266WebServer class

/** Constructor
 */
webServer::webServer(){
    // server = new ESP8266WebServer(80);  // Port 80 is the default port for HTTP
}
/** Initialize the web server
 */
void webServer::init(void) {
    boolean result =  WiFi.softAP("ESP8266", "123456789");
#ifdef DEBUG
    if (result) {
        Serial.printf("webServer::init - WiFi soft access point is running. [%lu ms]\n", millis());
    } else {
        Serial.printf("webServer::init - WiFi soft access point failed. [%lu ms]\n", millis());
    }
#endif
    IPAddress local_IP(192, 168, 0, 10);  // Set your desired IP address
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    result = WiFi.softAPConfig(local_IP, gateway, subnet);
#ifdef DEBUG
    if (result) {
        Serial.printf("webServer::init - AP Config Success. [%lu ms]\n", millis());
    } else {
        Serial.printf("webServer::init - AP Config Failed. [%lu ms]\n", millis());
    }
#endif
}
/** Load the web page
 */
void webServer::loadWebPage(void) {
    // Load the web page
    server.on("/", HTTP_GET, []() {
        server.send_P(200, "text/html", webPage_html);
    });
    server.begin(); 
#ifdef DEBUG
    Serial.printf("webServer::loadWebPage - Web server is running. [%lu ms]\n", millis());
#endif
}
/** Handle the client request
 */
void webServer::webServerHandler(void) {
    server.handleClient();
#ifdef DEBUG
   // Serial.printf("webServer::webServerHandler - webServer handleClient. [%lu ms]\n", millis());
#endif
}
/** Get the instance of the web server
 */
webServer* webServer::_getInstance(void) {
    static webServer instance;
    return &instance;
}
