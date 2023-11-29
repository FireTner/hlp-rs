#pragma once

#include "vec.h"

bool lastLayarable(const vec layer) {
  uint16_t a = 0;
  uint16_t b = 0;

  for(int i = 0; i < 16; i++) a |= 1 << (_mm_extract_epi8(layer, i));
  for(int i = 0; i < 16; i++) b |= 1 << (_mm_extract_epi8(goal, i));

  return b == (a & b);
}