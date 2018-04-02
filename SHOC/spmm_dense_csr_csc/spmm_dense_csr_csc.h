#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 64
#define M 64
#define K 64

#define NZA1 2016

#define NZA2 2006
/*
B:  1  0  0  0
    0  0  2  3
    0  0  0  0
    0  1  2  0

C:  0  4  0  1
    5  0  1  0
    0  1  2  0
    0  0  3  2

A:  0  4  0  1
    0  2  13 6
    0  0  0  0
    5  2  5  0

A(i,j) = B(i,k) * C(k,j)
*/

#define TACO_MIN(_a,_b) ((_a) < (_b) ? (_a) : (_b))
typedef enum { taco_mode_dense, taco_mode_sparse } taco_mode_t;
typedef struct {
  int      order;         // tensor order (number of modes)
  int*     dimensions;    // tensor dimensions
  int      csize;         // component size
  int*     mode_ordering; // mode storage ordering
  taco_mode_t* mode_types;    // mode storage types
  int*  indices[2][2];       // tensor index data (per mode)
  int*     vals;          // tensor values
} taco_tensor_t;


