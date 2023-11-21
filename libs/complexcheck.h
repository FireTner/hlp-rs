#pragma once

#include "vec.h"

int cmpfunc (const void * a, const void *b) {
   return (*(uint8_t*)b - *(uint8_t*)a);
}

char goalThing[16] = { [0 ... 15 ] = 0 };
void genGoalCheck() {
  for(int i = 0; i < 16; i++) {
    goalThing[goalArray[i]]++;
  }

  qsort(goalThing, 16, 1, cmpfunc);
}

bool complexCheck(const vec input) {
  char inputThing[16] = { [0 ... 15] = 0 };
  for(int i = 0; i < 16; i++) {
    inputThing[_mm_extract_epi8(input, i)]++;
  }
  qsort(inputThing, 16, 1, cmpfunc);

  int leftover = 0;
  for(int i = 0; i < 16; i++) {
    leftover += goalThing[i] - inputThing[i];

    if(leftover < 0)
      return false;
  }

  return true;
}