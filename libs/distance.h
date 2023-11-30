#pragma once

#include "vec.h"
#include "genlut.h"
#include "applylayer.h"

#include <stdint.h>
#include <string.h>

char distTable1[(1 << 20)];
char distTable2[(1 << 20)];
char distTable3[(1 << 20)];
char distTable4[(1 << 20)];
char distTable5[(1 << 20)];
int total1 = 0;
int total2 = 0;
int total3 = 0;
int total4 = 0;
int total5 = 0;
int distDepth = -1;

inline int doShit(const vec value, const int start) {
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

      if(distTable1[o] == dist && distTable1[input] == 100) {
        distTable1[input] = dist + 1;
        total1++;
      }
      if(distTable2[o] == dist && distTable2[input] == 100) {
        distTable2[input] = dist + 1;
        total2++;
      }
      if(distTable3[o] == dist && distTable3[input] == 100) {
        distTable3[input] = dist + 1;
        total3++;
      }
      if(distTable4[o] == dist && distTable4[input] == 100) {
        distTable4[input] = dist + 1;
        total4++;
      }
      if(distTable5[o] == dist && distTable5[input] == 100) {
        distTable5[input] = dist + 1;
        total5++;
      }
    }
  }
}

void initDistance() {
  memset(distTable1, 100, sizeof(distTable1));
  memset(distTable2, 100, sizeof(distTable2));
  memset(distTable3, 100, sizeof(distTable3));
  memset(distTable4, 100, sizeof(distTable4));
  memset(distTable5, 100, sizeof(distTable5));

  int a = doShit(goal, 0);
  int b = doShit(goal, 4);
  int c = doShit(goal, 8);
  int d = doShit(goal, 12);
  int e = doShit(goal, 2);

  distTable1[a] = 0;
  distTable2[b] = 0;
  distTable3[c] = 0;
  distTable4[d] = 0;
  distTable5[e] = 0;

  int Total = 0;
  int prevTotal = -1;

  while(Total != prevTotal) {
    prevTotal = Total;
    genDistanceTable(++distDepth);
    Total = total1 + total2 + total3 + total4 + total5;
    printf("%2d: \t1: %5d \t2: %5d \t3: %5d \t4: %5d \t5: %d\n", distDepth, total1, total2, total3, total4, total5);
  }

  distDepth--;
}

static inline bool distance(const vec value, const int threshold) {
  int a = doShit(value, 0);

  int b = doShit(value, 4);

  int c = doShit(value, 8);
  
  int d = doShit(value, 12);

  int e = doShit(value, 2);
  
  if(threshold > distDepth) return false;
  if(distTable1[a] > threshold) return true;
  if(distTable2[b] > threshold) return true;
  if(distTable3[c] > threshold) return true;
  if(distTable4[d] > threshold) return true;
  if(distTable5[e] > threshold) return true;
  return false;
}