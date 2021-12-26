//
// Created by swagger on 2021/12/25.
//

#include "LogBuffer.h"
#include <cstring>
#include <iostream>

using std::endl;
using std::cout;

Buffer::Buffer()
: current_(data_)
, length_(0)
{}

Buffer::~Buffer() {
}

bool Buffer::append(const char *data, int len) {
  if ( len < avail() ){
    memcpy(current_, data, len);
    current_ += len;
    length_ += len;
    return true;
  }else {
    return false;
  }
}


void Buffer::add(int len) {
  length_ += len;
  current_ += len;
}


int Buffer::len() {
  return length_;
}


int Buffer::avail() {
  return LOG_BUFFER_SIZE - length_;
}


char* Buffer::data() {
  return data_;
}


char* Buffer::current() {
  return current_;
}


void Buffer::show() {
  cout << "Buffer: " << data_ << endl;
}





