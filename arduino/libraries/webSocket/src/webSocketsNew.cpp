#include <webSocketsNew.h>

WebSocketsServer socket = WebSocketsServer(81);  // Create an instance of the WebSocketsServer class

/** Constructor
 */
webSocket::webSocket() {
    // socket = new WebSocketsServer(81);  // Port 81 is the default port for WebSockets
}
/** Initialize the web socket
 */
void webSocket::init(void) {
    // Initialize WebSocket server
    socket.begin();
    socket.onEvent([this](uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
        this->_event(num, type, payload, length);
    });
#ifdef DEBUG
    Serial.printf("webSocket::init - webSocket initialized. [%lu ms]\n", millis());
#endif
}
/** Handle the WebSocket event
 */
void webSocket::_event(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    String message = "RC_ESP8266> ";
    String text;
    String echoMessage;
    switch (type) {
        case WStype_DISCONNECTED:
          message += "Disconnected!";
          break;
        case WStype_CONNECTED:
          message += "Connected!";
          break;
        case WStype_TEXT:
          text = String((char*)payload);
          message += _executeCliCommand(text);
          socket.sendTXT(num, message);
          break;
        default:
          message += "Unknown event type!";
          break;
      }
#ifdef DEBUG
    Serial.printf("webSocket::event %s. [%lu ms]\n", message.c_str(), millis());
#endif
}
/** Execute the CLI command
 */
String webSocket::_executeCliCommand(String command) {
    String response = "\nCommand executed: ";
    response += command;
    // Add your command execution logic here
    // For example, you can parse the command and execute specific actions
    // For now, just return the command as a response
    return response;
}
/** Handle the WebSocket event
 */
void webSocket::webSocketHandler() {
    socket.loop();
#ifdef DEBUG
   // Serial.printf("webSocket::webSocketHandler - webSocket loop. [%lu ms]\n", millis());
#endif
}
/** Get the WebSocket instance
 */
webSocket* webSocket::_getInstance() {
    static webSocket instance;
    return &instance;
}