#pragma once

#include "vec.h"
#include "genlut.h"

inline bool lastLayer(const vec input, const int prevIndex) {
  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = vec_shuffle(layer[index], input);
    if(vec_equal(output, goal)) return true;
  }
  return false;
}