#pragma once

#include "vec.h"
#include "genlut.h"

int lastResult = 0;
inline bool lastLayer(const vec input, const int prevIndex) {
  for(int i = 0; i < layerSize; i++) {
    const vec output = vec_shuffle(layer[i], input);
    
    if(vec_equal(output, goal)) {
      lastResult = i;
      return true;
    }
  }

  return false;
}