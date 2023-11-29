#pragma once

#include "vec.h"
#include "unicount.h"

vec layer[800];
int layerConf[800];
int layerSize = 0;

int indexTable[800][800];
int indexTableSize[800];

int pairs = 0;

vec subComp(const vec a, const vec b) {
  return _mm_max_epi8(_mm_sub_epi8(a, b), _mm_setzero_si128());
}

vec comComp(const vec a, const vec b) {
  return  _mm_andnot_si128(_mm_cmplt_epi8(a, b), a);
}

vec layerf(const vec input, const int conf) {
  vec back = _mm_set1_epi8(conf & 15);
  vec side = _mm_set1_epi8((conf >> 4) & 15);

  switch((conf >> 8) & 7) {
    case 0: return _mm_max_epi8(comComp(back, input), comComp(input, side));
    case 1: return _mm_max_epi8(subComp(back, input), comComp(input, side));
    case 2: return _mm_max_epi8(comComp(back, input), subComp(input, side));
    case 3: return _mm_max_epi8(subComp(back, input), subComp(input, side));
    case 4: return _mm_max_epi8(subComp(back, input), comComp(side, input));
    default: return _mm_setzero_si128();
  }
}

void genLut(int targetuc) {
  const vec start = _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  
  for(int conf = 0; conf < (256 * 5); conf++) {
    const vec output = layerf(start, conf);
    
    if(vec_equal(start, output)) continue;
    if(_mm_test_all_zeros(output, output)) continue;
    if(ucount(output) < targetuc) continue;
    
    for(int i = 0; i < layerSize; i++) {
      if(vec_equal(layer[i], output)) goto end;
    }

    layerConf[layerSize] = conf;
    indexTable[799][layerSize] = layerSize;
    layer[layerSize++] = output;
    end: continue;
  }
  
  indexTableSize[799] = layerSize;

  for(int i = 0; i < layerSize; i++) {
    const vec output = layer[i];
    vec thisLayer[800];
    int thisSize = 0;

    for(int j = 0; j < layerSize; j++) {
      const vec output2 = vec_shuffle(layer[j], output);

      if(vec_equal(start, output2)) continue;
      if(ucount(output2) < targetuc) continue;

      for(int k = 0; k < layerSize; k++) {
        if(vec_equal(layer[k], output2)) goto end2;
      }

      // check if in this pair
      for(int k = 0; k < thisSize; k++) {
        if(vec_equal(thisLayer[k], output2)) goto end2;
      }

      // check if in other pairs
      for(int x = 0; x < i; x++) {
        for(int y = 0; y < indexTableSize[x]; y++) {
          const vec a = layer[x];
          const vec b = vec_shuffle(layer[indexTable[x][y]], a);

          if(vec_equal(output2, b)) goto end2;
        }
      }

      pairs++;
      thisLayer[thisSize] = output2;
      indexTable[i][thisSize++] = j;
      end2: continue;
    }
    indexTableSize[i] = thisSize;
  }
}