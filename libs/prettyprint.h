#pragma once

#include <stdio.h>

void printConf(const int conf) {
  int back = conf & 0xF;
  int side = (conf >> 4) & 0xF;

  switch((conf >> 8) & 7) {
    case 0: printf(" %1X,  %1X; ", back, side); break;
    case 1: printf("*%1X,  %1X; ", back, side); break;
    case 2: printf(" %1X, *%1X; ", back, side); break;
    case 3: printf("*%1X, *%1X; ", back, side); break;
    case 4: printf("-%1X, -%1X; ", back, side); break;
    default: printf("?"); break;
  }
}