#include <rtos.h>

/** Constructor
 */
rtos::rtos() {
    _sysTickTimer = 0;
    _taskCount = 0;
    _taskList = new Task[MAX_TASKS];
#ifdef DEBUG
    Serial.printf("rtos::rtos Constructor. [%lu ms]\n", millis());
#endif
}
/** Destructor
 */
rtos::~rtos() {
    delete[] _taskList; // Free memory allocated for task list
#ifdef DEBUG
    Serial.printf("rtos::~rtos Destructor. [%lu ms]\n", millis());
#endif
}
/** Initialize the RTOS
 */
void rtos::init(void) {
    timer::init();
    timer::interrupt(_sysTickHandler_10us);
#ifdef DEBUG
    Serial.printf("rtos::init Initialized. [%lu ms]\n", millis());
#endif
}
/** Add a task to the RTOS
 */
void rtos::addTask(function_callback pfuncExec, u_long cycleTimeRun_us) {
    rtos* rtosInstance = rtos::_getInstance();
    // Task count is between 0 and MAX_TASKS
    if (rtosInstance->_taskCount >= MAX_TASKS) {
        #ifdef DEBUG
            Serial.printf("rtos::addTask [error] Task count exceeded. [%lu ms]\n", millis());
        #endif
        return;
    }
    for(int i = 0; i < rtosInstance->_taskCount; i++) {
        if (rtosInstance->_taskList[i].pfuncExec == pfuncExec) {
            #ifdef DEBUG
                Serial.printf("rtos::addTask [error] Task with pfuncExec = %p already exists. [%lu ms]\n", pfuncExec, millis());
            #endif
            return;
        }
    }
    // Run time is between 1 ms and 100 ms
    if (cycleTimeRun_us > MAX_CYCLE_TIME) {
        cycleTimeRun_us = MAX_CYCLE_TIME;
        #ifdef DEBUG
            Serial.printf("rtos::addTask [warning] Run time of task exceeded. [%lu ms]\n", millis());
        #endif
    }
    if (cycleTimeRun_us < MIN_CYCLE_TIME) {
        cycleTimeRun_us = MIN_CYCLE_TIME;
        #ifdef DEBUG
            Serial.printf("rtos::addTask [warning] Run time of task is too short. [%lu ms]\n", millis());
        #endif
    }
    // Add the task to the list
    rtosInstance->_taskList[rtosInstance->_taskCount].pfuncExec = pfuncExec;
    rtosInstance->_taskList[rtosInstance->_taskCount].cycleTimeRun_us = cycleTimeRun_us;
    rtosInstance->_taskList[rtosInstance->_taskCount].state = TASK_READY;
#ifdef DEBUG
    Serial.printf("rtos::addTask pfuncExec = %p, cycleTimeRun_us = %lu, _taskCount = %d . [%lu ms]\n",
        rtosInstance->_taskList[rtosInstance->_taskCount].pfuncExec,  
        rtosInstance->_taskList[rtosInstance->_taskCount].cycleTimeRun_us,
        rtosInstance->_taskCount, 
        millis());
#endif
    // Increment the task count
    rtosInstance->_taskCount++;
}
/** Remove a task from the RTOS
 */
void rtos::removeTask(function_callback pfuncExec) {
    rtos* rtosInstance = rtos::_getInstance();
    for (int i = 0; i < rtosInstance->_taskCount; i++) {
        if (rtosInstance->_taskList[i].pfuncExec == pfuncExec) {
            for (int j = i; j < rtosInstance->_taskCount - 1; j++) {
                rtosInstance->_taskList[j] = rtosInstance->_taskList[j + 1];
            }
            rtosInstance->_taskCount--;
            break;
        }
    }
#ifdef DEBUG
    Serial.printf("rtos::removeTask Task with pfuncExec = %p removed. [%lu ms]\n", pfuncExec, millis());
#endif
}
/** Execute the tasks in the RTOS
 */ 
void rtos::executeTasks() {
    rtos* rtosInstance = rtos::_getInstance();
    for (int i = 0; i < rtosInstance->_taskCount; i++) {
        if (rtosInstance->_taskList[i].state == TASK_READY) {
            rtosInstance->_taskList[i].pfuncExec();
            rtosInstance->_taskList[i].state = TASK_WAITING;
            #ifdef DEBUG
                //Serial.printf("rtos::executeTasks Task with pfuncExec = %p executed. [%lu ms]\n", rtosInstance->_taskList[i].pfuncExec, millis());
            #endif
        }
    }
}
/** System tick handler
 */
void rtos::_sysTickHandler_10us(void) {
    // It is mandatory to run the pwmHandler() function in the interrupt service routine
    pwmHandler();
    rtos* rtosInstance = rtos::_getInstance();
    if (rtosInstance == nullptr) {
        #ifdef DEBUG
            Serial.printf("rtos: [error] RTOS instance is null. [%lu ms]\n", millis());
        #endif
        return;
    }
    rtosInstance->_sysTickTimer += INTERRUPT_PERIOD; // 10 us
    // Monitor and manage task states and execution times
    rtosInstance->_monitorTasks();
#ifdef DEBUG
    // It is not recommended to use Serial.print in an interrupt service routine
    // Serial.printf("rtos: System tick handler _sysTickTimer = %lu us\n", rtosInstance->_sysTickTimer);
#endif
}
/** Monitor and manage task states and execution times
 */
void rtos::_monitorTasks() {
    rtos* rtosInstance = rtos::_getInstance();
    // start from 1 to skip the idle task
    for (int i = 0; i < rtosInstance->_taskCount; i++) {
        if (rtosInstance->_taskList[i].state == TASK_READY) {
            continue;
        }
        if ((rtosInstance->_sysTickTimer % rtosInstance->_taskList[i].cycleTimeRun_us) == 0) {
            rtosInstance->_taskList[i].state = TASK_READY;
        }
    }
}
/** Get the rtosInstance of the RTOS
 */
rtos* rtos::_getInstance() {
    // Declare a static instance of the rtos class. This ensures that only one instance of the class exists.
    static rtos rtosInstance;
    // Return a pointer to the single instance of the rtos class.
    return &rtosInstance;
}
