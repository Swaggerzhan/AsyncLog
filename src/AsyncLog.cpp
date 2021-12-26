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

AsyncLog::AsyncLog(const string& basename)
: buffer_(1024 * 20)
, logFile_(basename)
, running_(false)
, totalLog_(0)
, persistLog_(0)
{
  start();
}

AsyncLog::~AsyncLog() {
  stop();
  long end = TimeStampDebug::Now();
  TimeStampDebug::diff(start_, end);
  cout << "total Log:" << totalLog_.getValue() << endl;
  cout << "persist Log: " << persistLog_.getValue() << endl;
}


void AsyncLog::append(const char *data, int len) {
  // claim
  int64_t seq = buffer_.claim();
  LogBuffer *logBuffer = buffer_.expose(seq);
  memcpy(logBuffer->data, data, len);
  logBuffer->len = len;
  // publish
  buffer_.publish(seq);
  totalLog_.fetch_add();
}

// thread
void AsyncLog::persist() {
  while (running_) {
     int64_t seq = buffer_.getReadSeq();
     LogBuffer* logBuffer = buffer_.getValuePointBySeq(seq);
     logFile_.append(logBuffer->data, logBuffer->len);
     // read commit
     buffer_.readDone(seq);
     persistLog_.fetch_add();
  }
}

void AsyncLog::start() {
  running_ = true;
  std::thread t(std::bind(&AsyncLog::persist, this));
  t.detach();
  start_ = TimeStampDebug::Now();
}


void AsyncLog::stop() {
  running_ = false;
}
