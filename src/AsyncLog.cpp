//
// Created by swagger on 2021/12/25.
//
#include "TimeStamp.h"
#include "AsyncLog.h"
#include <cstring>
#include <iostream>

using std::endl;
using std::cout;
using std::string;

AsyncLog::AsyncLog()
: buffer_(1024 * 20)
, logFile_(string("test.log"))
, running_(false)
{
  start();
}

AsyncLog::~AsyncLog() {
  long end = TimeStampDebug::Now();
  TimeStampDebug::diff(start_, end);
}


void AsyncLog::append(const char *data, int len) {
  // claim
  int64_t seq = buffer_.claim();
  LogBuffer *logBuffer = buffer_.expose(seq);
  memcpy(logBuffer->data, data, len);
  logBuffer->len = len;
  // publish
  buffer_.publish(seq);
}

// thread
void AsyncLog::persist() {
  cout << "Log Thread Start" << endl;
  while (running_) {
     int64_t seq = buffer_.getReadSeq();
     LogBuffer* logBuffer = buffer_.getValuePointBySeq(seq);
     logFile_.append(logBuffer->data, logBuffer->len);
     // read commit
     buffer_.readDone(seq);
  }
}

void AsyncLog::start() {
  running_ = true;
  std::thread t(std::bind(&AsyncLog::persist, this));
  t.detach();
  start_ = TimeStampDebug::Now();
}



