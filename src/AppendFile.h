//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_APPENDFILE_H
#define ASYNCLOG_APPENDFILE_H

#include <string>

class AppendFile {
public:

  AppendFile(std::string filename);

  ~AppendFile();

  void append(const char* data, int len);
  void fflush();

  off_t writtenBytes() const;


private:
  FILE* fp_;
  char buffer_[64 * 1024]; // 64KB
  off_t writtenBytes_; // bytes that has written
};



#endif //ASYNCLOG_APPENDFILE_H
