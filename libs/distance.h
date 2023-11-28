#pragma once

#include "vec.h"
#include "genlut.h"
#include "applylayer.h"

#include <stdint.h>
#include <string.h>

char distTable1[65536];
char distTable2[65536];
char distTable3[65536];
char distTable4[65536];
int total1 = 0;
int total2 = 0;
int total3 = 0;
int total4 = 0;
int distDepth = -1;

void genDistanceTable(int dist) {
  for(int input = 0; input < 65536; input++) {
    for(int layeri = 0; layeri < layerSize; layeri++) {
      int a = input & 0xF;
      int b = (input >> 4) & 0xF;
      int c = (input >> 8) & 0xF;
      int d = (input >> 12) & 0xF;
      
      vec inputv = _mm_setr_epi8(a, b, c, d, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      vec outputv = vec_shuffle(layer[layeri], inputv);

      int o  = _mm_extract_epi8(outputv, 0);
          o |= _mm_extract_epi8(outputv, 1) << 4;
          o |= _mm_extract_epi8(outputv, 2) << 8;
          o |= _mm_extract_epi8(outputv, 3) << 12;

      if(distTable1[o] == dist && (distTable1[input] > dist + 1)) {
        distTable1[input] = dist + 1;
        total1++;
      }
      if(distTable2[o] == dist && (distTable2[input] > dist + 1)) {
        distTable2[input] = dist + 1;
        total2++;
      }
      if(distTable3[o] == dist && (distTable3[input] > dist + 1)) {
        distTable3[input] = dist + 1;
        total3++;
      }
      if(distTable4[o] == dist && (distTable4[input] > dist + 1)) {
        distTable4[input] = dist + 1;
        total4++;
      }
    }
  }
}

void initDistance() {
  memset(distTable1, 100, sizeof(distTable1));
  memset(distTable2, 100, sizeof(distTable2));
  memset(distTable3, 100, sizeof(distTable3));
  memset(distTable4, 100, sizeof(distTable4));


  int a  = _mm_extract_epi8(goal, 12);
      a |= _mm_extract_epi8(goal, 13) << 4;
      a |= _mm_extract_epi8(goal, 14) << 8;
      a |= _mm_extract_epi8(goal, 15) << 12;

  int b  = _mm_extract_epi8(goal, 8);
      b |= _mm_extract_epi8(goal, 9) << 4;
      b |= _mm_extract_epi8(goal, 10) << 8;
      b |= _mm_extract_epi8(goal, 11) << 12;
  
  int c  = _mm_extract_epi8(goal, 4);
      c |= _mm_extract_epi8(goal, 5) << 4;
      c |= _mm_extract_epi8(goal, 6) << 8;
      c |= _mm_extract_epi8(goal, 7) << 12;
  
  int d  = _mm_extract_epi8(goal, 0);
      d |= _mm_extract_epi8(goal, 1) << 4;
      d |= _mm_extract_epi8(goal, 2) << 8;
      d |= _mm_extract_epi8(goal, 3) << 12;

  distTable1[a] = 0;
  distTable2[b] = 0;
  distTable3[c] = 0;
  distTable4[d] = 0;

  int Total = 0;
  int prevTotal = -1;

  while(Total != prevTotal) {
    prevTotal = Total;
    genDistanceTable(++distDepth);
    Total = total1 + total2 + total3 + total4;
    printf("%2d: \t1: %5d \t2: %5d \t3: %5d \t4: %5d\n", distDepth, total1, total2, total3, total4);
  }

  distDepth--;
}

static inline bool distance(const vec value, const int threshold) {
  int a  = _mm_extract_epi8(value, 12);
      a |= _mm_extract_epi8(value, 13) << 4;
      a |= _mm_extract_epi8(value, 14) << 8;
      a |= _mm_extract_epi8(value, 15) << 12;

  int b  = _mm_extract_epi8(value, 8);
      b |= _mm_extract_epi8(value, 9) << 4;
      b |= _mm_extract_epi8(value, 10) << 8;
      b |= _mm_extract_epi8(value, 11) << 12;
  
  int c  = _mm_extract_epi8(value, 4);
      c |= _mm_extract_epi8(value, 5) << 4;
      c |= _mm_extract_epi8(value, 6) << 8;
      c |= _mm_extract_epi8(value, 7) << 12;
  
  int d  = _mm_extract_epi8(value, 0);
      d |= _mm_extract_epi8(value, 1) << 4;
      d |= _mm_extract_epi8(value, 2) << 8;
      d |= _mm_extract_epi8(value, 3) << 12;
  
  if(threshold > distDepth) return false;
  if(distTable1[a] > threshold) return true;
  if(distTable2[b] > threshold) return true;
  if(distTable3[c] > threshold) return true;
  if(distTable4[d] > threshold) return true;
  return false;
}