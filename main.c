#include "vec.h"
#include "unicount.h"
#include "genlut.h"
#include "search.h"

#include <stdio.h>

int main() {
  goal = _mm_setr_epi8(0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 3, 0, 0, 1, 1, 0);
  vec_store(goal, &goalArray);
  
  printf("Goal: ");
  vec_print(goal);
  
  int goal_uc = ucount(goal);
  printf("Goal's unicount: %d\n", goal_uc);

  genLut(goal_uc);
  printf("Generated look up table with the size: %d\n", layerSize);
  
  search();
  
  return 0;
}