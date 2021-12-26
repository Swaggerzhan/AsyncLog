#include <iostream>
#include "src/TimeStamp.h"
#include "src/Atomic.h"
#include <unistd.h>
#include <thread>

#include "src/Log.h"


using std::cout;
using std::endl;
using std::string;

int loop = 1000000;

string name = "test";
AtomicInt64 count;


void thread1() {
  for (int i=0; i<loop; i ++) {
    Log() << "this is test data at: " << i;
    count.fetch_add();
  }
}

void thread2() {
  for (int i=0; i<loop; i ++) {
    Log(DEBUG) << "this is test data at: " << i;
    count.fetch_add();
  }
}

void thread3() {
  for (int i=0; i<loop; i ++) {
    Log(ERROR) << "this is test data at: " << i;
    count.fetch_add();
  }
}

void thread4() {
  for (int i=0; i<loop; i ++) {
    Log(FATAL) << "this is test data at: " << i;
    count.fetch_add();
  }
}


int main() {

  long start = TimeStampDebug::Now();
  std::thread t1(thread1);
  std::thread t2(thread2);
  std::thread t3(thread3);
  std::thread t4(thread4);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  long end = TimeStampDebug::Now();
  TimeStampDebug::diff(start, end);
  cout << "Log Num: " << count.getValue() << endl;
  return 0;

}
