#include "vec.h"
#include "unicount.h"
#include "genlut.h"
#include "search.h"

#include <stdio.h>

int main() {
  // 13,13,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1,15
  // 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
  goal = _mm_setr_epi8(0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 3, 0, 0, 1, 1, 0);
  // goal = vec_shuffle(goal, _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
  vec_store(goal, &goalArray);
  
  printf("Goal: ");
  vec_print(goal);
  
  int goal_uc = ucount(goal);
  printf("Goal's unicount: %d\n", goal_uc);

  genLut(goal_uc);
  printf("Generated look up table with the size: %d\n", layerSize);
  
  // for(int i = 0; i < layerSize; i++) {
  //   printf("\t%3d: %3d\n", i, indexTableSize[i]);
  // }
  
  search();
  
  return 0;
}