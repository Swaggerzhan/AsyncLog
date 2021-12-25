//
// Created by swagger on 2021/12/25.
//

#include "Disruptor.h"


int64_t risePowerOfTwo(int64_t value) {
  value |= value >> 1;
  value |= value >> 2;
  value |= value >> 4;
  value |= value >> 8;
  value |= value >> 16;
  return value + 1;
}


