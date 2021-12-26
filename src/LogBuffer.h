//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_LOGBUFFER_H
#define ASYNCLOG_LOGBUFFER_H

#define LOG_BUFFER_SIZE 128


class Buffer {
public:
  Buffer();
  ~Buffer();

  bool append(const char* data, int len);
  char* data();
  char* current();
  int avail();
  int len();
  void add(int len);

  // for debug
  void show();


private:
  char data_[LOG_BUFFER_SIZE];
  char* current_;
  int length_;

};





#endif //ASYNCLOG_LOGBUFFER_H
