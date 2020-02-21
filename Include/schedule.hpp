#include <avr/io.h>			//include for base avr funcs
#include <util/atomic.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>


namespace schedule
{
  const uint16_t            scheduleQueueMaxLen = 20;
  const uint16_t            scheduleAdditQueueOnceMaxLen = 4;             //will be allocated in once queue

  extern volatile uint16_t  scheduleCounter,                              //2  bytes
                            scheduleQueueLen,		                          //2  bytes
                            scheduleAdditQueueLen;                        //2  bytes
  extern struct _Task       tasksMainLoop[scheduleQueueMaxLen];           //80 bytes
  extern struct _Task       tasksAdditOnce[scheduleAdditQueueOnceMaxLen]; //16 bytes
  //                                                                TOTAL: 102 bytes


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


  void _setTaskQueue(const struct Task tasks[], const size_t len);
  void _setTaskQueue(void(*funcs[])(), const size_t len);


  template<class T, size_t N>
  constexpr void setTaskQueue(T (&tasks)[N])
  {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      static_assert(N <= scheduleQueueMaxLen, "Len of given array more than max schedule task queue len");
      _setTaskQueue(tasks, N);
    }
  }

} //namespace schedule