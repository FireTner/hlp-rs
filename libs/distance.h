#pragma once

#include "vec.h"
#include "genlut.h"
#include "applylayer.h"

#include <stdint.h>
#include <string.h>

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int abs(x) {
  if(x < 0) return -x;
  return x;
}

static inline bool distance(const vec value, const int threshold) {
  int arr[16];
  for(int i = 0; i < 16; i++) { //zip(start, goal)
    arr[i] = (_mm_extract_epi8(value, i) << 4) | _mm_extract_epi8(goal, i);
  }
  qsort(arr, 16, sizeof(int), cmpfunc); //sorted()
  int total = 0;
  for(int i = 0; i < 15; i++) {//"big jump" magic
    if(abs((arr[i] & 15) - (arr[i + 1] & 15)) > abs(((arr[i] >> 4) & 15) - ((arr[i + 1] >> 4) & 15))) total++;
  }

  return total > threshold; //if distance is too far return 1 to prune it
}