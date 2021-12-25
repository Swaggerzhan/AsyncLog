cmake_minimum_required(VERSION 3.20)
project(AsyncLog)

set(CMAKE_CXX_STANDARD 14)

add_executable(AsyncLog main.cpp src/Disruptor.h src/Disruptor.cpp src/Atomic.h src/Atomic.cpp src/LogBuffer.h src/LogBuffer.cpp src/AppendFile.h src/AppendFile.cpp src/AsyncLog.h src/AsyncLog.cpp src/TimeStamp.h src/TimeStamp.cpp)
