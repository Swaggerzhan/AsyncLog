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
#ifdef DEBUG
, totalLog_(0)
, persistLog_(0)
#endif
{
  start();
}

AsyncLog::~AsyncLog() {
  stop_and_join();
  long end = TimeStampDebug::Now();
#ifdef DEBUG
  TimeStampDebug::diff(start_, end);
  cout << "total Log:" << totalLog_.getValue() << endl;
  cout << "persist Log: " << persistLog_.getValue() << endl;
#endif
}


void AsyncLog::append(const char *data, int len) {
  // claim
  int64_t seq = buffer_.claim();
  LogBuffer *logBuffer = buffer_.expose(seq);
  memcpy(logBuffer->data, data, len);
  logBuffer->len = len;
  // publish
  buffer_.publish(seq);
#ifdef DEBUG
  totalLog_.fetch_add();
#endif
}

// thread
void AsyncLog::persist() {
  while (running_) {
     int64_t seq = buffer_.getReadSeq();
     LogBuffer* logBuffer = buffer_.getValuePointBySeq(seq);
     logFile_.append(logBuffer->data, logBuffer->len);
     // read commit
     buffer_.readDone(seq);
#ifdef DEBUG
     persistLog_.fetch_add();
#endif
  }
}

void AsyncLog::start() {
  running_ = true;
  threads_ = std::thread(std::bind(&AsyncLog::persist, this));
  //t.detach();  join at exit()!
#ifdef DEBUG
  start_ = TimeStampDebug::Now();
#endif
}


void AsyncLog::stop_and_join() {
  running_ = false;
  threads_.join();
}
