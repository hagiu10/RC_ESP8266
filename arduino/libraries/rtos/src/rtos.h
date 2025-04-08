#ifndef RTOS_H
#define RTOS_H

#include <commonLibs.h>
#include <timer.h>
#include <pwmSignal.h>

#ifndef u_long
#define u_long unsigned long
#endif

#define MAX_TASKS 10U
#define INTERRUPT_PERIOD 10U // 10 us
#define MAX_CYCLE_TIME 1000000UL // 1000 ms
#define MIN_CYCLE_TIME 1000U // 1ms

// Function pointer
typedef void (*function_callback)  ();
// Task structure
typedef struct {
  function_callback pfuncExec;
  u_long cycleTimeRun_us;
  uint8_t state;
} Task;
// Enumeration for task states
enum taskState {
  TASK_WAITING,
  TASK_READY,
  TASK_STATE_COUNT
};
// Function prototypes
class rtos: private timer, private pwmSignal {
  private:
    u_long _sysTickTimer;
    uint8_t _taskCount;
    Task* _taskList;
    static void _sysTickHandler_10us(void);
    static rtos* _getInstance(void);
    void _monitorTasks(void);
  public:
    rtos();
    ~rtos();
    void init(void);
    void addTask(function_callback pfuncExec, u_long cycleTimeRun_us);
    void removeTask(function_callback pfuncExec);
    void executeTasks(void);  
};
#endif // RTOS_H