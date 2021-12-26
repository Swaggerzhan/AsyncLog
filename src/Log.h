//
// Created by swagger on 2021/12/26.
//

#ifndef ASYNCLOG_LOG_H
#define ASYNCLOG_LOG_H

#include <string>

#define LOG_BUFFER_SIZE 128

class AsyncLog;

enum LEVEL{
  INFO,
  DEBUG,
  ERROR,
  FATAL,
};

class Log {
public:

  Log(LEVEL level=INFO);
  ~Log();

  Log& operator << (int);
  Log& operator << (long);
  Log& operator << (std::string);

  // for debug

  void show();

private:

  void initTime();

  size_t avail();
  void append(const char* data, int len);
  char* current();
  void add(size_t len);

  template<typename T>
  void formatInteger(T v);

  static void LogInit();
  static AsyncLog* ins();

private:

  static AsyncLog* asyncLog;
  static const int kMaxNumericSize = 48;


  // buffer
  char buffer_[LOG_BUFFER_SIZE];
  off_t written_;


  static const char* kINFO;
  static const char* kDEBUG;
  static const char* kERROR;
  static const char* kFATAL;

};




#endif //ASYNCLOG_LOG_H
