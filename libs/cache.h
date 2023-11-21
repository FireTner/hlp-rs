#pragma once

#include "vec.h"

#include <string.h>

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
  uint32_t pos = hash(key) & cacheMask;
  const bool a = cache[pos].depth <= depth && vec_equal(cache[pos].key, key);

  cache[pos].depth = depth;
  cache[pos].key = key;
  
  return a;
}