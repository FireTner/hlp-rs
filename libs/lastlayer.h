#pragma once

#include "vec.h"
#include "distance.h"

static inline bool lastLayer(const vec input, const int prevIndex) {
  if(distance(input, 1)) return false;

  for(int i = 0; i < layerSize; i++) {
    const vec output = vec_shuffle(layer[i], input);
    iter++;
    if(vec_equal(output, goal)) {
      result[currentLayer] = layerConf[i];
      return true;
    }
  }

  return false;
}