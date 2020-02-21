#include <avr/io.h>			//include for base avr funcs
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>
#include <util/atomic.h>

#include "schedule.hpp"

void foo()
{

}

void bar()
{

}

const struct schedule::Task tasks[] = {{foo, 1}, {bar, 2}};

int main()
{
    struct schedule::Task task = {foo, 1};
    schedule::setTaskQueue(tasks);
    return task.quantsWanted;
}
