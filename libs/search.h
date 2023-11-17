#pragma once

#include "vec.h"
#include "genlut.h"
#include "cache.h"
#include "applylayer.h"
#include "lastlayer.h"

#include <time.h>

int currentLayer = 0;
bool dfs(const vec input, const int depth, const int prevIndex) {
  if(depth == currentLayer) return lastLayer(input, prevIndex);
  if(inCache(input, depth)) return false;

  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = applyLayer(input, index);

    if(_mm_test_all_zeros(output, output)) continue;
    if(dfs(output, depth + 1, index)) return true;
  }

  return false;
}

void search() {
  const vec start = _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

  float startTime = clock() / (CLOCKS_PER_SEC / 1000);

  while(currentLayer < 42) {
    clearCache();
    if(dfs(start, 0, 799)) break;
    currentLayer++;
    printf("\t%d layer searched in %.0f ms\n", currentLayer, clock() / (CLOCKS_PER_SEC / 1000) - startTime);
  }

  printf("Solution is %d deep\n", currentLayer + 1);
  printf("Found in %.0f ms\n", clock() / (CLOCKS_PER_SEC / 1000) - startTime);
}