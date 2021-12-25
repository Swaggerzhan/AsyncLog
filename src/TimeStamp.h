//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_TIMESTAMP_H
#define ASYNCLOG_TIMESTAMP_H


class TimeStampDebug{
public:

  static long Now();

  // for debug
  static void diff(long start, long end);


public:

  static long kSecond2MicroSecond;

};


#endif //ASYNCLOG_TIMESTAMP_H
