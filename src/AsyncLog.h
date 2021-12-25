//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_ASYNCLOG_H
#define ASYNCLOG_ASYNCLOG_H

#include "Disruptor.h"
#include "AppendFile.h"
#include <thread>

#define LOG_LINE_SIZE 128

typedef struct {
  char data[LOG_LINE_SIZE];
  int len;
}LogBuffer;

class AsyncLog {
public:
  AsyncLog();
  ~AsyncLog();

  void append(const char* data, int len);

private:
  void start();
  void persist();

private:
  Disruptor<LogBuffer> buffer_;
  AppendFile logFile_;

  bool running_;


  // for debug
  long start_;

};




#endif //ASYNCLOG_ASYNCLOG_H
