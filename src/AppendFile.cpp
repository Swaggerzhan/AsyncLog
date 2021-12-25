//
// Created by swagger on 2021/12/25.
//


#include "AppendFile.h"
#include <cassert>
#include <fstream>

// for debug
#include <iostream>

using std::cout;
using std::endl;


AppendFile::AppendFile(std::string filename)
        : fp_(::fopen(filename.c_str(), "ae"))
        , writtenBytes_(0)
{
  assert(fp_);
  ::setbuffer(fp_, buffer_, sizeof buffer_);
  //cout << "create file at: " << filename.c_str() << endl;
}

AppendFile::~AppendFile() {
  fflush();
  ::fclose(fp_);
}

void AppendFile::append(const char *data, int len) {
  size_t written = 0;
  while ( written != len ) {
    size_t remain = len - written;
#ifdef __APPLE__
    size_t n = ::fwrite(data+written, 1, remain, fp_);
#endif

#ifdef __linux__
    size_t n = ::fwrite_unlocked(data + written, 1, remain, fp_);
#endif
    //cout << "len: " << len << endl;
    //cout << "n: " << n << " remain: " << remain << endl;
    //assert(n == remain );

    written += n;
  }
  writtenBytes_ += written;
}

void AppendFile::fflush() {
  ::fflush(fp_);
}


off_t AppendFile::writtenBytes() const {
  return writtenBytes_;
}


