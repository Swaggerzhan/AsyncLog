//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_ASYNCLOG_H
#define ASYNCLOG_ASYNCLOG_H

#include "Disruptor.h"
#include "LogFile.h"
#include <thread>


typedef struct {
  char data[128];
  int len;
}LogBuffer;


class AsyncLog {
public:
  AsyncLog(const std::string& basename);
  ~AsyncLog();

  void append(const char* data, int len);

private:
  void start();
  void stop_and_join();
  void persist();

private:
  Disruptor<LogBuffer> buffer_;
  LogFile logFile_;

  std::atomic<bool> running_;
  std::thread threads_;

  // for debug
#ifdef DEBUG
  long start_;
  AtomicInt64 totalLog_;
  AtomicInt64 persistLog_;
#endif

};




#endif //ASYNCLOG_ASYNCLOG_H
