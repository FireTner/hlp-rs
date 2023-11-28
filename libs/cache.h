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

int hit = 0, miss = 0, new = 0;
inline bool inCache(const vec key, const int depth) {
  uint32_t pos = 0; 
  for(int i = 0; i < 4; i++) {
    pos = _mm_crc32_u32(pos, _mm_extract_epi32(key, i));
  }

  pos &= cacheMask;

  const bool a = cache[pos].depth <= depth && vec_equal(cache[pos].key, key);

  if(a) hit++;
  else if(vec_equal(cache[pos].key, _mm_setzero_si128())) new++;
  else miss++;

  cache[pos].depth = depth;
  cache[pos].key = key;
  
  return a;
}