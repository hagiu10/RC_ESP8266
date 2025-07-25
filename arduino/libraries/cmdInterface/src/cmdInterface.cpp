#include <cmdInterface.h>

/** Constructor
 */
cmdInterface::cmdInterface(){
    // Constructor implementation
}
/** Init function 
 */
void cmdInterface::init() {
    // Initialization code here
}
/**
 * Exec function
 * This function executes the command line interface.
 * Command line must have a structure like: 'cmd' 'arg1' 'arg2' ... 'argN'
 * The first argument is the command name, and the rest are arguments for that command.
 */
String cmdInterface::executeCmd(String cmdLine) {
    String message;
    cmdLine.trim();
    String args[MAX_ARGS]; // Fixed-size array for up to maximum number of arguments
    int argCount = 0;

    int startIndex = 0;
    int spaceIndex = cmdLine.indexOf(' ');

    while (spaceIndex != -1 && argCount < MAX_ARGS) {
        args[argCount++] = cmdLine.substring(startIndex, spaceIndex);
        startIndex = spaceIndex + 1;
        spaceIndex = cmdLine.indexOf(' ', startIndex);
    }

#ifdef DEBUG
    printf("cmdInterface::executeCmd Command received: %s. [%lu ms]\n", cmdLine.c_str(), millis());
#endif

    if (argCount < 1) {
        message = "Invalid command format. Use: 'cmd' 'arg1' 'arg2' ... 'argN'";
        return message;
    }

    String cmd = args[0];

    if (cmd.equalsIgnoreCase(message = "start")) {
        if (argCount < 1) {
            message = "Error: Missing test name. Use: start 'taskName'";
            return message;
        }
        String taskName = args[1];
        changeStateTask(taskName,TASK_READY);
        message = "Task '";
        message += taskName;
        message += "' started.";
        return message;
    } else if (cmd.equalsIgnoreCase(message = "stop")) {
        if (argCount < 1) {
            message = "Error: Missing test name. Use: stop 'taskName'" ;
            return message;
        }
        String taskName = args[1];
        changeStateTask(taskName,TASK_BLOCKED);
        message = "Task '";
        message += taskName;
        message += "' stopped.";
    } else if (cmd.equalsIgnoreCase(message = "help")) {
        message = HELP_TEXT;
        return message;
    } 

    message = "Unknown command: ";
    message += cmd;
    message += ". Use 'help' for available options.";
    return message;  
}
