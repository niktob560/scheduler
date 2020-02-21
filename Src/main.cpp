#include <avr/io.h>			//include for base avr funcs
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>
#include <util/atomic.h>

#include "schedule.hpp"


void foo(){}

void bar(){}


struct schedule::Task tasks[] = {{foo, 1}, {bar, 2}, {foo, 3}, {foo, 4}};



int main()
{
    schedule::setTaskQueue(tasks);
    return 0;
}
