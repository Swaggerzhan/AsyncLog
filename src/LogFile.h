//
// Created by swagger on 2021/12/26.
//

#ifndef ASYNCLOG_LOGFILE_H
#define ASYNCLOG_LOGFILE_H

#include <string>
#include <unistd.h>

class AppendFile;

class LogFile {
public:

  LogFile(const std::string& basename);
  ~LogFile();

  void append(const char* data, int len);

private:

  void rollLog();

  std::string getFileName();

private:

  std::string basename_;

  AppendFile* file_;

  size_t rollSize_;

};





#endif //ASYNCLOG_LOGFILE_H
