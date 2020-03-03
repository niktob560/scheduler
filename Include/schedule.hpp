#include <avr/io.h> //include for base avr funcs
#include <util/atomic.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

namespace schedule
{
const uint16_t 		scheduleQueueMaxLen = 20;
const uint16_t 		scheduleAdditQueueOnceMaxLen = 4; //will be allocated in once queue

extern uint16_t 	scheduleCounter,								//2  bytes
					scheduleQueueLen,								//2  bytes
					scheduleAdditQueueLen;							//2  bytes
extern uint8_t 		quantsElapsed;									//1  byte
extern struct Task 	tasksMainLoop[scheduleQueueMaxLen];			  	//60 bytes
extern struct Task 	tasksAdditOnce[scheduleAdditQueueOnceMaxLen];  	//12 bytes
//-----------------------------------------------------------------------------
//                                                             TOTAL: 79 bytes

struct Task
{
	void (*func)();		  //2 bytes
	uint8_t quantsWanted; //1 byte
};
//3 bytes


   /*
    *	Function:	scheduleAddFunc
    *	Desc:		Add func to repeat by schedule (adding instead of idle)(have side-effects)
	*						quantsWanted field will be set to 1
    *	Input:			void* func: ptr to func
    *	Output:		none
    */
void scheduleAddFunc(void (*func)());

   /*
    *	Function:	scheduleAddFunc
    *	Desc:		Add func to execute once by schedule (adding instead of idle)(have side-effects)
	*						quantsWanted field will be set to 1
    *	Input:			void* func: ptr to func
    *	Output:		none
    */
void scheduleAddOnceFunc(void (*func)());


   /*
    *	Function:	scheduleAddTask
    *	Desc:		Add func to repeat by schedule (adding instead of idle)(have side-effects)
    *	Input:			const struct Task task: task struct
    *	Output:		none
    */
void scheduleAddTask(const struct Task task);

   /*
    *	Function:	scheduleAddOnceTask
    *	Desc:		Add func to execute once by schedule (adding instead of idle)(have side-effects)
    *	Input:			const struct Task task: task struct
    *	Output:		none
    */
void scheduleAddOnceTask(const struct Task task);


   /*
    *	Function:	_setTaskQueue
    *	Desc:		Set queue for looping execution	(have side-effects)
    *	Input:			const struct Task tasks[]: 	array of tasks
	*					const size_t len:			num of tasks in array
    *	Output:		none
    */
void _setTaskQueue(const struct Task tasks[], const size_t len);

   /*
    *	Function:	_setTaskQueue
    *	Desc:		Set queue for looping execution(only for func array, quantsWanted will be set at 1 for each once)(have side-effects)
    *	Input:			void (*funcs[])(): 	array of void(void) funcs
	*					const size_t len:	num of tasks in array
    *	Output:		none
    */
void _setTaskQueue(void (*funcs[])(), const size_t len);


   /*
    *	Function:	_setOnceTaskQueue
    *	Desc:		Set queue for once execution(have side-effects)
    *	Input:			const struct Task tasks[]: 	array of tasks
	*					const size_t len:			num of tasks in array
    *	Output:		none
    */
void _setOnceTaskQueue(const struct Task tasks[], const size_t len);


   /*
    *	Function:	_setOnceTaskQueue
    *	Desc:		Set queue for once execution(only for func array, quantsWanted will be set at 1 for each once)(have side-effects)
    *	Input:			void (*funcs[])(): 	array of void(void) funcs
	*					const size_t len:	num of tasks in array
    *	Output:		none
    */
void _setOnceTaskQueue(void (*funcs[])(), const size_t len);


   /*
    *	Function:	setTaskQueue
    *	Desc:		Array proxy for _setTaskQueue funcs for beauty interface with brace-enclosed initializer list
    *	Input:			T (&tasks)[N]: 	array of tasks or void(void) funcs with size of N
    *	Output:		none
    */
template <class T, size_t N>
constexpr void setTaskQueue(T (&tasks)[N])
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		static_assert(N <= scheduleQueueMaxLen, "Len of given array for looped execution more than max schedule task queue len");
		_setTaskQueue(tasks, N);
	}
}

   /*
    *	Function:	setOnceTaskQueue
    *	Desc:		Array proxy for _setOnceTaskQueue funcs for beauty interface with brace-enclosed initializer list
    *	Input:			T (&tasks)[N]: 	array of tasks or void(void) funcs with size of N
    *	Output:		none
    */
template <class T, size_t N>
constexpr void setOnceTaskQueue(T (&tasks)[N])
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		static_assert(N <= scheduleAdditQueueOnceMaxLen, "Len of given array for once execution more than max schedule task queue len");
		_setOnceTaskQueue(tasks, N);
	}
}


   /*
    *	Function:	schedule
    *	Desc:		Run next task or skip if not all wanted quants elapsed
	*					call from timer, please
    *	Input:		none
    *	Output:		none
    */
void schedule(void);

} //namespace schedule