#pragma once

#include "vec.h"
#include "lastlayer.h"
#include "applylayer.h"
#include "cache.h"
#include "genlut.h"

#define MAX_DEPTH (43)

int result[MAX_DEPTH] = { [0 ... MAX_DEPTH - 1] = 0 };
int currentLayer = 0;
bool dfs(const vec input, const int depth, const int prevIndex) {
  if(depth == currentLayer) return lastLayer(input, prevIndex);
  if(inCache(input, depth)) return false;

  __builtin_prefetch(layer);
  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = applyLayer(input, index);

    if(_mm_test_all_zeros(output, output)) continue;
    if(dfs(output, depth + 1, index)) {
      result[depth] = index;
      return true;
    }
  }

  return false;
}