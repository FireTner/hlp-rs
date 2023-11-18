#pragma once

#include <stdint.h>
#include <string.h>

#include "vec.h"

#define CACHE_SIZE 1 << 18

const int cacheMask = CACHE_SIZE - 1;

struct {
  vec key;
  int depth;
} cache[CACHE_SIZE];

inline void clearCache() {
  memset(&cache, 0, sizeof(cache));
}

inline bool inCache(const vec value, const int depth) {
  uint64_t pos = 0;
  pos = _mm_crc32_u64(_mm_extract_epi64(value, 1), _mm_extract_epi64(value, 0));

  pos &= cacheMask;
  
  if(cache[pos].depth <= depth && vec_equal(cache[pos].key, value)) return true;

  cache[pos].depth = depth;
  cache[pos].key = value;

  return false;
}