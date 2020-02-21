#include <avr/io.h>			//include for base avr funcs
#include <util/atomic.h>


namespace schedule
{
  const uint16_t scheduleQueueMaxLen = 20;
  const uint16_t scheduleSubqueueOnceMaxLen = 4;                   //will be allocated in once queue

  extern volatile uint16_t  scheduleCounter,    //2 bytes
                            scheduleQueueLen,		//2 bytes
                            subscheduleQueueLen;//2 bytes
  extern void (*scheduleQueue[scheduleQueueMaxLen])();			              //scheduleQueueMaxLen bytes
  extern void (*scheduleSubqueueOnce[scheduleSubqueueOnceMaxLen])();			//scheduleSubqueueOnceMaxLen bytes
  //Total SRAM usage: scheduleQueueOnceMaxLen + scheduleSubqueueOnceMaxLen + 6 bytes
  //                  30 bytes


  /*
   *	Function:	scheduleAddFunc
   *	Desc:		  Add func to repeat by schedule (adding instead of idle)
   *	Input:		void* func: ptr to func
   *	Output:		none
   */
  void scheduleAddFunc(void(* func)());


} //namespace schedule
