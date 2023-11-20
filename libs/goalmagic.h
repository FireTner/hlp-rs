#pragma once

#include "vec.h"

void genMagic() {
  for(int i = 0; i < 15; i++) {
    vec a = _mm_set1_epi8(goalArray[i]);
    goalMagic[i] = ~_mm_movemask_epi8(_mm_cmpeq_epi8(goal, a));
  }
}