#pragma once

#include "vec.h"
#include "genlut.h"
#include "applylayer.h"

#include <stdint.h>
#include <string.h>

#define DISTANCE_ELEMENTS 5

const int distOffsets[DISTANCE_ELEMENTS] = { 0, 4, 8, 12, 2 };
char distTable[DISTANCE_ELEMENTS][(1 << 20)];
int total[DISTANCE_ELEMENTS];
int distDepth = -1;

inline uint64_t doShit(const vec value, const int start) {
  int a  = _mm_extract_epi8(value, (start + 0) & 0xF);
      a |= _mm_extract_epi8(value, (start + 1) & 0xF) << 4;
      a |= _mm_extract_epi8(value, (start + 2) & 0xF) << 8;
      a |= _mm_extract_epi8(value, (start + 3) & 0xF) << 12;
      a |= _mm_extract_epi8(value, (start + 4) & 0xF) << 16;
  return a;
}

void genDistanceTable(int dist) {
  for(int input = 0; input < (1 << 20); input++) {
    for(int layeri = 0; layeri < layerSize; layeri++) {
      if(dist == 0 && !lastLayerTable[layeri]) continue;

      int a = input & 0xF;
      int b = (input >> 4) & 0xF;
      int c = (input >> 8) & 0xF;
      int d = (input >> 12) & 0xF;
      int e = (input >> 16) & 0xF;
      
      vec inputv = _mm_setr_epi8(a, b, c, d, e, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      vec outputv = vec_shuffle(layer[layeri], inputv);

      int o  = _mm_extract_epi8(outputv, 0);
          o |= _mm_extract_epi8(outputv, 1) << 4;
          o |= _mm_extract_epi8(outputv, 2) << 8;
          o |= _mm_extract_epi8(outputv, 3) << 12;
          o |= _mm_extract_epi8(outputv, 4) << 16;

#pragma GCC unroll 16
      for(int i = 0; i < DISTANCE_ELEMENTS; i++) {
        if(distTable[i][o] == dist && distTable[i][input] == 100) {
          distTable[i][input] = dist + 1;
          total[i]++;
        }
      }
    }
  }
}

void initDistance() {
  int Total = 0;
  int prevTotal = -1;

  memset(total, 0, sizeof(total));

#pragma GCC unroll 16
  for(int i = 0; i < DISTANCE_ELEMENTS; i++) {
    memset(distTable[i], 100, sizeof(distTable[i]));
    int offset = doShit(goal, distOffsets[i]);
    distTable[i][offset] = 0;
  }

  while(Total != prevTotal) {
    prevTotal = Total;
    genDistanceTable(++distDepth);
    printf("%2d: ", distDepth);

    Total = 0;
    for(int i = 0; i < DISTANCE_ELEMENTS; i++) {
      Total += total[i];
      printf("\t%d: %5d ", i + 1, total[i]);
    }
    printf("\n");
  }

  distDepth--;
}

static inline bool distance(const vec value, const int threshold) {
  if(threshold > distDepth) return false;

#pragma GCC unroll 16
  for(int i = 0; i < DISTANCE_ELEMENTS; i++) {
    int offset = doShit(value, distOffsets[i]);
    if(distTable[i][offset] > threshold) return true;
  }

  return false;
}