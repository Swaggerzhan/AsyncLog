//
// Created by swagger on 2021/12/25.
//

#include "TimeStamp.h"
#include <iostream>
#include <sys/time.h>


using std::endl;
using std::cout;


long TimeStampDebug::kSecond2MicroSecond = 1000 * 1000;

long TimeStampDebug::Now() {
  timeval now{};
  gettimeofday(&now, nullptr);
  return now.tv_sec * kSecond2MicroSecond + now.tv_usec;
}


void TimeStampDebug::diff(long start, long end) {
  long interval = end - start;
  if ( interval <= 0 ) {
    cout << "end <= start!" << endl;
    return;
  }
  cout << interval / kSecond2MicroSecond << " s ";
  cout << interval % kSecond2MicroSecond << " ms" << endl;
}
