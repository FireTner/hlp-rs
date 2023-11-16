#pragma once

#include "vec.h"
#include "genlut.h"
#include "cache.h"

#include <time.h>

inline vec applyLayer(const vec input, const int index) {
  char map[16] = {[0 ... 15] = -1};
  vec result = vec_shuffle(layer[index], input);

  int8x16 resultArray;
  vec_store(result, &resultArray);
  
  for(int i = 0; i < 16; i++) {
    const char ri = resultArray[i];
    const char x = map[ri];
  
    if(x != -1 && x != goalArray[i])
      return _mm_setzero_si128();
    
    map[ri] = goalArray[i];
  }

  return result;
}

inline bool lastLayer(const vec input, const int prevIndex) {
  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = vec_shuffle(layer[index], input);
    if(vec_equal(output, goal)) return true;
  }
  return false;
}

int currentLayer = 0;
bool dfs(const vec input, const int depth, const int prevIndex) {
  if(depth == currentLayer) return lastLayer(input, prevIndex);
  if(inCache(input, depth)) return false;

  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = applyLayer(input, index);

    if(vec_equal(output, _mm_setzero_si128())) continue;
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
    printf("\t%d layer searched in %.0f ms\n", currentLayer, clock() / (CLOCKS_PER_SEC / 1000) - startTime);
    currentLayer++;
  }

  printf("Solution is %d deep\n", currentLayer + 1);
  printf("found in %.0f ms\n", clock() / (CLOCKS_PER_SEC / 1000) - startTime);
}