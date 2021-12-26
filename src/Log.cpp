//
// Created by swagger on 2021/12/26.
//

#include "Log.h"
#include "AsyncLog.h"
#include <sys/time.h>

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;

const char* Log::kINFO = "[INFO] ";
const char* Log::kDEBUG = "[DEBUG]";
const char* Log::kERROR = "[ERROR]";
const char* Log::kFATAL = "[FATAL]";

AsyncLog* Log::asyncLog = nullptr;
static pthread_once_t logInit = PTHREAD_ONCE_INIT;


// for time
__thread static char stringTimeBuf[128];
__thread static time_t storeTime = 0;


AsyncLog* Log::ins() {
  pthread_once(&logInit, LogInit);
  return asyncLog;
}

void Log::LogInit(){
  asyncLog = new AsyncLog("test");
}

template<typename T>
size_t convert(char buf[], T value)
{
  T i = value;
  char* p = buf;

  do
  {
    int lsd = static_cast<int>(i % 10);
    i /= 10;
    *p++ = zero[lsd];
  } while (i != 0);

  if (value < 0)
  {
    *p++ = '-';
  }
  *p = '\0';
  std::reverse(buf, p);

  return p - buf;
}

void Log::initTime() {
  timeval now{};
  gettimeofday(&now, nullptr);
  if (now.tv_sec == storeTime) {
  }else {
    struct tm tm{};
    gmtime_r(&now.tv_sec, &tm);
    memset(stringTimeBuf, '\0', sizeof(stringTimeBuf));
    strftime(stringTimeBuf, sizeof stringTimeBuf, "(%Y.%m.%d-%H:%M:%S.", &tm);
    storeTime = now.tv_sec;
  }
  append(stringTimeBuf, strlen(stringTimeBuf));
  size_t len = convert(current(), now.tv_usec);
  add(len);
  append("us). ", 5);
}


Log::Log(LEVEL level)
: written_(0)
{
  memset(buffer_, '\0', LOG_BUFFER_SIZE);
  if (level == INFO){
    append(kINFO, strlen(kINFO));
  }else if (level == DEBUG) {
    append(kDEBUG, strlen(kDEBUG));
  }else if (level == ERROR) {
    append(kERROR, strlen(kERROR));
  }else {
    append(kFATAL, strlen(kFATAL));
  }
  initTime();
}

Log::~Log() {
  if (avail() > 1){
    memcpy(current(), "\n", 1);
    add(1);
  }
  assert( ins() != nullptr );
  ins()->append(buffer_, written_);
}


template<typename T>
void Log::formatInteger(T v) {
  if (avail() > kMaxNumericSize) {
    size_t len = convert(current(), v);
    add(len);
  }
}

/////

Log& Log::operator<<(int v) {
  formatInteger(v);
  return *this;
}

Log& Log::operator<<(long v) {
  formatInteger(v);
  return *this;
}

Log& Log::operator<<(std::string v) {
  if (avail() > v.size()) {
    memcpy(current(), v.c_str(), v.size());
    add(v.size());
  }
  return *this;
}


// private
size_t Log::avail() {
  return LOG_BUFFER_SIZE - written_;
}

char* Log::current() {
  return buffer_ + written_;
}

void Log::add(size_t len) {
  written_ += len;
}

void Log::append(const char *data, int len) {
  memcpy(current(), data, len);
  add(len);
}

// for debug
void Log::show() {
  cout << "Buffer: " << buffer_ << endl;
}
