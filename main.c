#include "vec.h"
#include "complexcheck.h"
#include "applylayer.h"
#include "genlut.h"
#include "search.h"

#include <stdio.h>

int main() {
  goal = _mm_setr_epi8(3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3);
  vec_store(goal, &goalArray);
  
  printf("Goal: ");
  vec_print(goal);
  
  genGoalMap();
  genGoalCheck();

  genLut();
  printf("Generated look up table with the size: %d\n", layerSize);

  search();

  return 0;
}