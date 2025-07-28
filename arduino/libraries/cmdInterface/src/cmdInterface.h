#ifndef CMDINTERFACE_H
#define CMDINTERFACE_H

#include <commonLibs.h>
#include <rtos.h>

#define MAX_ARGS 5 // Maximum number of arguments
#define HELP_TEXT "Available commands:\n" \
          "  start 'teskName' - Start a task\n" \
          "  stop 'teskName' - Stop a task\n" \
          "  help - Show this help message\n" \
          "  List of task's names:\n" \
          "   - blinkLed\n"

// Function prototypes
class cmdInterface: private rtos {
  public:
    cmdInterface();
    static void init(void);
    static String executeCmd(String cmdLine);
    static void testCLI();
};
#endif // CMDINTERFACE_H
