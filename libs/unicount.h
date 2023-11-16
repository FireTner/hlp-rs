#pragma once

#include "vec.h"

int ucount(const vec value) {
  int8x16 temp;
  int count = 16;
  
  vec_store(value, &temp);

  for(int i = 0; i < 16; i++) {
    for(int j = i + 1; j < 16; j++) {
      if(temp[i] == temp[j]) {
        count--;
        break;
      }
    }
  }

  return count;
}