cmake_minimum_required(VERSION 3.20)

project(AsyncLog)

include_directories(../)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 14)

add_executable(AsyncLog muti.cpp 
  ../src/Disruptor.h ../src/Disruptor.cpp 
  ../src/Atomic.h ../src/Atomic.cpp 
  ../src/LogBuffer.h ../src/LogBuffer.cpp 
  ../src/AppendFile.h ../src/AppendFile.cpp 
  ../src/AsyncLog.h ../src/AsyncLog.cpp 
  ../src/TimeStamp.h ../src/TimeStamp.cpp 
  ../src/LogFile.h ../src/LogFile.cpp 
  ../src/Log.h ../src/Log.cpp)
