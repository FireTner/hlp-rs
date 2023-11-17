#pragma once

#include "vec.h"
#include "genlut.h"

inline vec applyLayer(const vec input, const int index) {
  vec result = vec_shuffle(layer[index], input);

  int8x16 resultArray;
  vec_store(result, &resultArray);
  
  for(int i = 0; i < 16; i++) {
    const vec a = _mm_set1_epi8(resultArray[i]);
    const short b = _mm_cmpeq_epi8_mask(result, a);
    const short c = goalMagic[i];
    
    if(b & c) return _mm_setzero_si128();
  }

  return result;
}