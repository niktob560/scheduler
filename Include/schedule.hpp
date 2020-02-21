#include <avr/io.h>			//include for base avr funcs
#include <util/atomic.h>
#include <stdint.h>


namespace schedule
{
  const uint16_t scheduleQueueMaxLen = 20;
  const uint16_t scheduleAdditQueueOnceMaxLen = 4;                   //will be allocated in once queue

  extern volatile uint16_t  scheduleCounter,                          //2 bytes
                            scheduleQueueLen,		                      //2 bytes
                            scheduleAdditQueueLen;                    //2 bytes
  extern struct _Task       tasksMainLoop[scheduleQueueMaxLen];       //80 bytes
  extern struct _Task       tasksAdditOnce[scheduleAdditQueueOnceMaxLen]; //16 bytes
  //                                                             TOTAL: 102 bytes


   /*
    *	Function:	scheduleAddFunc
    *	Desc:		  Add func to repeat by schedule (adding instead of idle)
    *	Input:		void* func: ptr to func
    *	Output:		none
    */
  void scheduleAddFunc(void(* func)());

  struct Task
  {
    void (* func)();      //2 bytes
    uint8_t quantsWanted; //1 byte
  };
  //3 bytes

  struct _Task: Task
  {
    uint8_t quantsElapsed = 0;  //1 byte
  };
  //4 bytes

  struct Task createTask(void(* func)());
  struct Task createTask(void(* func)(), uint8_t quantsWanted);
  void setTaskQueue(const struct Task tasks[]);
  void setTaskQueue(const void(*funcs[])());

} //namespace schedule