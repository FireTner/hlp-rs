#pragma once

#include "vec.h"
#include "genlut.h"

void genGoalMap() {
  for(int i = 0; i < 15; i++) {
    goalMagic[i] = ~makemask(goal, _mm_set1_epi8(goalArray[i]));
  }
}

inline vec applyLayer(const vec input, const int index) {
  vec result = vec_shuffle(layer[index], input);
  int8x16 resultArray;
  vec_store(result, &resultArray);
  
  for(int i = 0; i < 15; i++) {
    const int a = makemask(result, _mm_set1_epi8(resultArray[i]));
    const int b = goalMagic[i];

    if(a & b) return _mm_setzero_si128();
  }

  return result;
}