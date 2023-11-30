#pragma once

#include "vec.h"
#include "distance.h"

static inline bool lastLayer(const vec input, const int prevIndex) {
  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const vec output = vec_shuffle(layer[indexTable[prevIndex][i]], input);
    iter++;
    if(vec_equal(output, goal)) {
      result[currentLayer] = layerConf[indexTable[prevIndex][i]];
      return true;
    }
  }

  return false;
}