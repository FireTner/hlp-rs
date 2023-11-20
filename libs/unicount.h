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

int cmpfunc (const void * a, const void * goalThing) {
   return -(*(uint8_t*)a - *(uint8_t*)goalThing);
}

bool complexCheck(const vec input) {
  char inputThing[16] = { [0 ... 15] = 0 };
  for(int i = 0; i < 16; i++) {
    inputThing[_mm_extract_epi8(input, i)]++;
  }
  qsort(inputThing, 16, 1, cmpfunc);

  char goalThing[16] = { [0 ... 15] = 0 };
  for(int i = 0; i < 16; i++) {
    goalThing[goalArray[i]]++;
  }
  qsort(goalThing, 16, 1, cmpfunc);

  // printf("%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x\n",
  //   goalThing[0], goalThing[1], goalThing[2], goalThing[3], goalThing[4], goalThing[5], goalThing[6], goalThing[7], goalThing[8], goalThing[9], goalThing[10], goalThing[11], goalThing[12], goalThing[13], goalThing[14], goalThing[15]);
  // printf("%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x\n",
  //   inputThing[0], inputThing[1], inputThing[2], inputThing[3], inputThing[4], inputThing[5], inputThing[6], inputThing[7], inputThing[8], inputThing[9], inputThing[10], inputThing[11], inputThing[12], inputThing[13], inputThing[14], inputThing[15]);

  int leftover = 0;
  for(int i = 0; i < 16; i++) {
    leftover += goalThing[i] - inputThing[i];

    if(leftover < 0)
      return false;
  }

  return true;
}