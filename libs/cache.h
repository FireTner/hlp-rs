#pragma once

#include <stdint.h>
#include <string.h>

#include "vec.h"

const int cacheMask = 1023;

struct {
  vec key;
  int depth;
} cache[1024];

inline void clearCache() {
  memset(&cache, 0, sizeof(cache));
}

inline bool inCache(const vec value, const int depth) {
  const vec shiftedValue = _mm_bsrli_si128(value, 60);
  const vec oredvalue = _mm_or_si128(shiftedValue, value);
  const uint64_t x = _mm_cvtsi128_si64(value);
  uint64_t h = x * 0x9E3779B97F4A7C15L;
  uint32_t pos = (h ^= h >> 32) & cacheMask;

  vec cachedValue = cache[pos].key;
  
  if(cache[pos].depth <= depth && vec_equal(cache[pos].key, value)) return true;

  cache[pos].depth = depth;
  cache[pos].key = value;
  return false;
}