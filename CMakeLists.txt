cmake_minimum_required(VERSION 3.20)
project(AsyncLog)

set(CMAKE_BUILD_TYPE RELEASE)

set(CMAKE_CXX_STANDARD 14)

add_library(AsyncLog
        src/Disruptor.h src/Disruptor.cpp
        src/Atomic.h src/Atomic.cpp
        src/LogBuffer.h src/LogBuffer.cpp
        src/AppendFile.h src/AppendFile.cpp
        src/AsyncLog.h src/AsyncLog.cpp
        src/TimeStamp.h src/TimeStamp.cpp
        src/LogFile.h src/LogFile.cpp
        src/Log.h src/Log.cpp)


set(INSTALL_HEAD_FILES src/Log.h)

install(
        TARGETS AsyncLog
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(
        FILES ${INSTALL_HEAD_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

