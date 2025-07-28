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
    socket.onEvent(webSocket::onSocketEventStatic);
#ifdef DEBUG
    Serial.printf("webSocket::init - webSocket initialized. [%lu ms]\n", millis());
#endif
}

// Static event handler to be passed to socket.onEvent
void webSocket::onSocketEventStatic(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    webSocket* instance = webSocket::_getInstance();
    if (instance) {
        instance->_event(num, type, payload, length);
    }
}
/** Handle the WebSocket event
 */
void webSocket::_event(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    String message;
    message.concat("RC_ESP8266> ");
    String text;
    String echoMessage;
    switch (type) {
        case WStype_DISCONNECTED:
          message += "Disconnected!\n";
          break;
        case WStype_CONNECTED:
          message += "Connected!\n";
          break;
        case WStype_TEXT:
          text.concat((char*)payload);
          message += executeCmd(text);
          message = formatTextMessage(message);
          socket.sendTXT(num, message);
          break;
        default:
          message += "Unknown event type!\n";
          break;
      }
#ifdef DEBUG
    Serial.printf("webSocket::event Time event: [%lu ms]\n", millis());
    Serial.printf("webSocket::event %s", message.c_str());
#endif
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
/** Add in text massage for each '\n' a '<br>'
 * This is used to format the text message for HTML display
 */
String webSocket::formatTextMessage(String & text) {
    String formattedText;
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == '\n') {
            formattedText += "<br>\n";
        } else {
            formattedText += text[i];
        }
    }
    return formattedText;
}