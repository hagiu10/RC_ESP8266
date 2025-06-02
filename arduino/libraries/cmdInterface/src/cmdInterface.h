#ifndef CMDINTERFACE_H
#define CMDINTERFACE_H

#include <commonLibs.h>
#include <rtos.h>

#define MAX_ARGS 5 // Maximum number of arguments
#define HELP_TEXT "Available commands:\n" \
          "  start 'testName' - Start a test\n" \
          "  stop 'testName' - Stop a test\n" \
          "  help - Show this help message\n" \
          "  List functions name:\n" \
          "   - testDutyCycle\n"

// Function prototypes
class cmdInterface: private rtos {
  public:
    cmdInterface();
    void init(void);
    String executeCmd(String cmdLine);
    static void testCLI();
};
#endif // CMDINTERFACE_H
