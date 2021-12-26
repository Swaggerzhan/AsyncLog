//
// Created by swagger on 2021/12/25.
//

#ifndef ASYNCLOG_DISRUPTOR_H
#define ASYNCLOG_DISRUPTOR_H


#include "Atomic.h"
#include <thread>
#include <iostream>

using std::endl;
using std::cout;

int64_t risePowerOfTwo(int64_t value);


template<typename T>
class Disruptor {
public:

  Disruptor(int64_t length=1024)
          : writeCursor_(0)
          , commitWriteCursor_(-1)
          , readCursor_(-1)
          , commitRead_(-1)
          , length_(risePowerOfTwo(length))
          , M_(length_ - 1)
  {
    ringBuffer_ = new T[length_];
  }
  ~Disruptor(){
    delete ringBuffer_;
  }

  int64_t claim() {
    int64_t seq = writeCursor_.fetch_add();
    while ( seq - commitRead_.getValue() > length_ ) {

    }
    return seq;
  }

  T* expose(int64_t seq) {
    return &ringBuffer_[seq & M_];
  }

  void publish(int64_t seq) {
    while ( seq - 1 != commitWriteCursor_.getValue() ) {}
    commitWriteCursor_.store(seq);
  }


  void push(T value) {
    int64_t seq = writeCursor_.fetch_add();
    while ( seq - commitRead_.getValue() > length_ ) {
      // spin
    }
    ringBuffer_[seq & M_] = value;

    // commit
    while ( seq - 1 != commitWriteCursor_.getValue()) {
      // spin
    }
    // update
    commitWriteCursor_.store(seq);
    //cout << "push success" << endl;
  }

  int64_t getReadSeq() {
    int64_t seq = readCursor_.add_fetch();
    while ( seq > commitWriteCursor_.getValue() ){
      // spin
      std::this_thread::yield();
    }
    return seq;
  }

  T* getValuePointBySeq(int64_t seq) {
    return &ringBuffer_[seq & M_];
  }

  T getValueBySeq(int64_t seq) {
    return ringBuffer_[seq & M_];
  }

  void readDone(int64_t seq) {
    while ( seq - 1 != commitRead_.getValue() ) {
      // spin
    }
    // update
    commitRead_.store(seq);
  }

private:

  AtomicInt64 writeCursor_;
  AtomicInt64 commitWriteCursor_;

  AtomicInt64 readCursor_;
  AtomicInt64 commitRead_;

  T* ringBuffer_;
  int64_t length_;
  int64_t M_;

};


#endif //ASYNCLOG_DISRUPTOR_H
