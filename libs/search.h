#pragma once

#include "vec.h"
#include "genlut.h"
#include "cache.h"
#include "applylayer.h"
#include "lastlayer.h"
#include "dfs.h"

#include <time.h>

void search() {
  // DON'T CHANGE THIS CONSTANT //
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
    printf("\n");
  }

  printf("Solution is %d deep\n", currentLayer + 1);
  printf("Found in %.0f ms\n", clock() / (CLOCKS_PER_SEC / 1000) - startTime);

  result[currentLayer] = lastResult;
  for(int i = 0; i <= currentLayer; i++) {
    const int conf = layerConf[result[i]];
    printf("%d: %3x\n", i, conf);
  }
}