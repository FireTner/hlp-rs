#include "vec.h"
#include "unicount.h"
#include "goalmagic.h"
#include "genlut.h"
#include "search.h"

#include <stdio.h>

int main() {
  goal = _mm_setr_epi8( 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3);
  vec_store(goal, &goalArray);
  
  printf("Goal: ");
  vec_print(goal);
  
  int goal_uc = ucount(goal);
  printf("goal's unicount: %d\n\n", goal_uc);

  genLut(goal_uc);
  printf("Generated look up table with the size: %d\n", layerSize);
  
  genMagic();  
  search();

  return 0;
}