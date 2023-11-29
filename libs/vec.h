#pragma once

#include <x86intrin.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#ifndef START_DEPTH
#define START_DEPTH 6
#endif

typedef __m128i vec;
typedef char __attribute__ ((aligned (16))) int8x16[16];

vec goal;
int8x16 goalArray;
int goalMagic[16];
int currentLayer = START_DEPTH - 1;
int result[50];
unsigned long iter = 0;

inline void vec_store(const vec source, int8x16 *destination) {
  _mm_store_si128((__m128i *)destination, source);
}

inline vec vec_load(int8x16 *source) {
  return _mm_load_si128((__m128i *)&source);
}

inline bool vec_equal(const vec a, const vec b) {
  const vec c = _mm_xor_si128(a, b);
  return _mm_test_all_zeros(c, c);
}

inline vec vec_shuffle(const vec value, const vec mask) {
  return _mm_shuffle_epi8(value, mask);
}

inline uint64_t vec_compact(const vec value, const int index) {
  return _mm_extract_epi16(value, index) | (_mm_extract_epi16(value, index + 1) << 4);
}

void vec_print(const vec a) {
  int8x16 b;
  vec_store(a, &b);

  printf("%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x%1x\n",
    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);
}