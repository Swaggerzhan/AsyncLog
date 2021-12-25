#include <iostream>
#include "src/AsyncLog.h"
#include "src/TimeStamp.h"
#include <unistd.h>

using std::cout;
using std::endl;

int loop = 10000000;
char data[] = "11111111111111111111111111111111\n";
int len = sizeof(data);

AsyncLog myLog;


void thread1() {
  for (int i=0; i<loop; i ++) {
    myLog.append(data, len);
  }
}


int main() {

  long start = TimeStampDebug::Now();
  std::thread t1(thread1);
  std::thread t2(thread1);
  std::thread t3(thread1);
  std::thread t4(thread1);
  t1.join();
  t2.join();
  t3.join();
  t4.join();


}
