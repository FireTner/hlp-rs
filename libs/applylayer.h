#pragma once

#include "vec.h"
#include "genlut.h"

inline vec applyLayer(const vec input, const int index) {
  vec result = vec_shuffle(layer[index], input);

  int8x16 resultArray;
  vec_store(result, &resultArray);
  
  for(int i = 0; i < 15; i++) {
    const vec a = _mm_set1_epi8(resultArray[i]);
    const int b = _mm_movemask_epi8(_mm_cmpeq_epi8(result, a));

    const int c = goalMagic[i];

    if(b & c) return _mm_setzero_si128();
  }

  return result;
}