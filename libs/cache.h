#pragma once

#include <stdint.h>
#include <string.h>

#include "vec.h"

#define CACHE_SIZE (1 << 25)

const int cacheMask = CACHE_SIZE - 1;

struct {
  vec key;
  int depth;
} cache[CACHE_SIZE];

inline void clearCache() {
  memset(&cache, 0, sizeof(cache));
}

inline bool inCache(const vec key, const int depth) {
  uint64_t pos = _mm_extract_epi64(key, 1) | (_mm_cvtsi128_si64(key) << 4);
  pos *= 0x9E3779B97F4A7C15L;
  pos ^= pos >> 32; 
  pos &= cacheMask;

  const bool a = cache[pos].depth <= depth && vec_equal(cache[pos].key, key);

  // if(a) hit++;
  // else if(vec_equal(cache[pos].key, _mm_setzero_si128())) new++;
  // else miss++;

  cache[pos].depth = depth;
  cache[pos].key = key;
  
  return a;
}