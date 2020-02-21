#include "schedule.hpp"

namespace schedule
{

  void (*scheduleQueue[scheduleQueueMaxLen])();			              //SCH_MAX_LEN bytes
  void (*scheduleSubqueueOnce[scheduleSubqueueOnceMaxLen])();			//SCH_MAX_LEN bytes

  volatile uint16_t scheduleCounter = 0,    //2 bytes
                    scheduleQueueLen = 0,		//2 bytes
                    subscheduleQueueLen = 0;//2 bytes


  /*
   *	Function:	scheduleAddFunc
   *	Desc:		  Add func to repeat by schedule (adding instead of idle)
   *	Input:		void* func: ptr to func
   *	Output:		none
   */
  void scheduleAddFunc(void(* func)())
  {
    #ifdef TRY_SORT
      for(uint16_t i = 0; i < scheduleQueueLen; i++)
      {
        if(scheduleQueue[i] == 0)
        {
          ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
          {
            scheduleQueue[i] = func;
          }
          return;
        }
      }
    #endif
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      if(scheduleQueueLen < scheduleQueueLen)
      {
        scheduleQueue[scheduleQueueLen] = func;
        scheduleQueueLen++;
      }
    }
  }

} //namespace schedule
