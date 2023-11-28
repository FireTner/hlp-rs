#pragma once

#include "vec.h"
#include "genlut.h"
#include "cache.h"
#include "applylayer.h"
#include "lastlayer.h"
#include "distance.h"
#include "prettyprint.h"

#include <time.h>

#ifdef PROFILE
#define MAX_DEPTH 8
#else
#define MAX_DEPTH 42
#endif


bool dfs(const vec input, const int depth, const int prevIndex) {
  if(depth == currentLayer) return lastLayer(input, prevIndex);
  if(inCache(input, depth)) return false;

  __builtin_prefetch(layer);
  for(int i = 0; i < indexTableSize[prevIndex]; i++) {
    const int index = indexTable[prevIndex][i];
    const vec output = applyLayer(input, layer[index]);

    if(_mm_test_all_zeros(output, output)) continue;

    if(distance(output, currentLayer - depth)) continue;

    if(dfs(output, depth + 1, index)) {
      result[depth] = layerConf[index];
      return true;
    }
  }

  return false;
}

void search() {
  const vec start = _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  float startTime = clock() / (CLOCKS_PER_SEC / 1000);
  char outstr[30];

  while(currentLayer < MAX_DEPTH) {
    clearCache();

    if(dfs(start, 0, 799)) break;
    currentLayer++;

    time_t currentTime = time(0);
    struct tm *cTime = localtime(&currentTime);
    strftime(outstr, sizeof(outstr), "%H:%M:%S", cTime);

    printf("[%s]", outstr);
    printf(" Depth %d searched", currentLayer);
    printf(" in %.0f ms", clock() / (CLOCKS_PER_SEC / 1000) - startTime);
    printf(" (%u itterations)\n", iter);
    printf("\tHits: %d \tMisses: %d \tInitialized: %d\n\n", hit, miss, new);
    // printf(" (%d, %d, %d [%.4f])\n", hit, miss, new, ((float)hit)/miss);

    miss = 0;
    new = 0;
    hit = 0;
    iter = 0;
  }

  printf("Solution is %d deep\n", currentLayer + 1);
  printf("Found in %.0f ms\n", clock() / (CLOCKS_PER_SEC / 1000) - startTime);

  for(int i = 0; i <= currentLayer; i++) {
    printConf(result[i]);
  }
  printf("\n");
}

// 9811205747
//   91980559