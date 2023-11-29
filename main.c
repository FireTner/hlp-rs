#include "vec.h"
#include "unicount.h"
#include "goalmagic.h"
#include "genlut.h"
#include "distance.h"
#include "search.h"

#include <stdio.h>

// 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 -> 8 deep
// 1, 1, 2, 3, 5, 8, 1, 3, 2, 1, 3, 4, 5, 5, 8, 9 -> 7 deep
// 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 -> 4 deep
// 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8 -> 3 deep
// 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 4, 4, 4, 4 -> 3 deep
// 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3 -> pi

int main() {
  goal = _mm_setr_epi8(3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3);
  vec_store(goal, &goalArray);
  
  printf("Goal: ");
  vec_print(goal);

  printf("\n");
  
  int goal_uc = ucount(goal);
  printf("goal's unicount: %d\n\n", goal_uc);

  genLut(goal_uc);
  printf("Generated look up table with the size: %d (%d)\n", layerSize, pairs);
  
  initDistance();
  genMagic();

  search();

  return 0;
}