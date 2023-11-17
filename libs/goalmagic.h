#pragma once

#include "vec.h"

void genMagic() {
  for(int i = 0; i < 16; i++) {
    vec a = _mm_set1_epi8(goalArray[i]);
    goalMagic[i] = _mm_cmpneq_epi8_mask(goal, a);
  }
}