//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_ATOMIC_H
#define ASYNCLOG_ATOMIC_H

#include <atomic>


#ifndef CACHE_LINE_BYTES

#define CACHE_LINE_BYTES 64
#define PADDING_SIZE_FOR_INT64 \
  (CACHE_LINE_BYTES - sizeof(std::atomic<int64_t>))

#endif



class AtomicInt64{
public:
  AtomicInt64();
  AtomicInt64(int64_t init);
  ~AtomicInt64();

  // get old value and add 1
  int64_t fetch_add();
  // get new value after add 1
  int64_t add_fetch();

  void store(int64_t target);
  int64_t getValue();


private:
  char padding0[PADDING_SIZE_FOR_INT64];
  std::atomic<int64_t> value_;
  char padding1[PADDING_SIZE_FOR_INT64];
};


#endif //ASYNCLOG_ATOMIC_H
