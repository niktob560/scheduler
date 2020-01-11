cmake_minimum_required(VERSION 3.1)

project(scheduler)

include_directories(Include)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -Wall -Wextra -std=gnu++11 -g -Werror")
set(mainSRCS main Src/main.cpp)
#set(libSRCS )


add_executable(${mainSRCS})
#ADD_LIBRARY(fantastic_train SHARED ${libSRCS})

#target_link_libraries(main)

#ADD_LIBRARY(fantastic-train SHARED ${libSRCS})


