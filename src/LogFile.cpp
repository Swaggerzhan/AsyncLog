//
// Created by swagger on 2021/12/26.
//
#include "LogFile.h"
#include "AppendFile.h"
#include <sys/time.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

LogFile::LogFile(const string& basename)
: basename_(basename)
, file_(nullptr)
, rollSize_(1024 * 1024 * 256) // 256MB
{
  rollLog();
  assert(file_ != nullptr);
}

LogFile::~LogFile() {
  delete file_;
}

void LogFile::append(const char *data, int len) {
  file_->append(data, len);
  if (file_->writtenBytes() > rollSize_){
    rollLog();
  }
}

void LogFile::rollLog() {
  delete file_;
  string filename = getFileName();
  file_ = new AppendFile(filename);
}

string LogFile::getFileName() {
  string filename;
  filename.reserve(basename_.size() + 64);
  filename = basename_;
  char timeBuf[32];
  struct tm tm{};
  time_t now = time(nullptr);
  gmtime_r(&now, &tm);
  strftime(timeBuf, sizeof timeBuf, ".%Y%m%d-%H-%M%S.", &tm);

  filename += timeBuf;
  filename += std::to_string(getpid());
  filename += ".log";
  return filename;
}



