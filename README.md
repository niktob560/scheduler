# scheduler

How to build:
```bash
mkdir /path/to/build
cd /path/to/build
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/project/cmake-avr/generic-gcc-avr.cmake /path/to/project
make
```
-----
How to use:  
* Don't  
-----
Warning!
=====
This thing have troubles with dynamic edition of main task loop  
Don't try to change main task loop after starting scheduler not in additional task queue as last element of queue
