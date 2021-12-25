//
// Created by swagger on 2021/12/25.
//
#include "Atomic.h"

AtomicInt64::AtomicInt64()
{
  value_.store(0, std::memory_order_release);
}

AtomicInt64::AtomicInt64(int64_t init)
{
  value_.store(init, std::memory_order_release);
}

AtomicInt64::~AtomicInt64() {

}

int64_t AtomicInt64::fetch_add() {
  return value_.fetch_add(1);
}

int64_t AtomicInt64::add_fetch() {
  return value_.fetch_add(1) + 1;
}

void AtomicInt64::store(int64_t target) {
  value_.store(target, std::memory_order_release);
}

int64_t AtomicInt64::getValue() {
  return value_.load(std::memory_order_acquire);
}
