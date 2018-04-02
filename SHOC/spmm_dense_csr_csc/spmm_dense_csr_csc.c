#include "spmm_dense_csr_csc.h"
#include "spmm_dense_csr_csc-data.h"

int spmm_dense_csr_csc(int* A0, int n, int m, int A12_pos[N+1], int A22_pos[K+1], int* A12_idx, int* A22_idx, int* A1_vals, int* A2_vals) {

  int t;

  int i3A1, i4A2;
  for (i3A1 = 0; i3A1 < n; i3A1++) {
    for (i4A2 = 0; i4A2 < m; i4A2++) {
      int ti5 = 0;
      int32_t pA12 = A12_pos[i3A1];
      int32_t pA22 = A22_pos[i4A2];
      int32_t pA22_bound = A22_pos[i4A2+1];

      inner: while ((pA12 < A12_pos[i3A1 + 1]) && (pA22 < pA22_bound)) {
        int32_t i5A1 = A12_idx[pA12];
        int32_t i5A2 = A22_idx[pA22];
        int32_t i5 = TACO_MIN(i5A1,i5A2);

        // TODO: move inside the if condition
        int b = A2_vals[pA22];

        if ((i5A1 == i5) && (i5A2 == i5)) {
          ti5 += A1_vals[pA12] * b;
        }
        if (i5A1 == i5) pA12++;
        if (i5A2 == i5) pA22++;
      }
      if ( ti5 != 0 ) {
        A0[i3A1*m + i4A2] = ti5;
      }
    }
  }
  return 0;
}

int main() {


/*
  int A12_pos[N+1];
  int A12_idx[NZA1];
  int A1_vals[NZA1];

  int A22_pos[K+1];
  int A22_idx[NZA2];
  int A2_vals[NZA2];
*/

  int i, j, k;
  int* A0 = (int*)malloc(sizeof(int)*(N*M));

//  #include "spmm_dense_csr_csc-data.h"


  int* A12_pos = (int*)malloc(sizeof(int)*(N+1));
  int* A12_idx = (int*)malloc(sizeof(int)*(NZA1));
  int* A1_vals = (int*)malloc(sizeof(int)*(NZA1));

  int* A22_pos = (int*)malloc(sizeof(int)*(K+1));
  int* A22_idx = (int*)malloc(sizeof(int)*(NZA2));
  int* A2_vals = (int*)malloc(sizeof(int)*(NZA2));

//  printf("countA1*4 : %d, countA2*4: %d\n", countA1*4, countA2*4);
 
  int A1_vptr = 0;
  A12_pos[0] = 0;


  for ( i = 0; i < N; i++ )
    for ( j = 0; j < M; j++ )
      A0[i*M+j] = 0;

  for ( i = 0; i < N; i++ ) {
    for ( j = 0; j < K; j++ ) {
      if ( A1[i][j] != 0 ) {
        A12_idx[A1_vptr] = j;
        A1_vals[A1_vptr] = A1[i][j];
        A1_vptr++;
      }
    }
    A12_pos[i+1] = A1_vptr;
  }

  int A2_vptr = 0;
  A22_pos[0] = 0;
  for ( j = 0; j < K; j++ ) {
    for ( i = 0; i < M; i++ ) {
      if ( A2[i][j] != 0 ) {
        A22_idx[A2_vptr] = i;
        A2_vals[A2_vptr] = A2[i][j];
        A2_vptr++;
      }
    }
    A22_pos[j+1] = A2_vptr;
  }

  spmm_dense_csr_csc(A0, N, M, A12_pos, A22_pos, A12_idx, A22_idx, A1_vals, A2_vals);

  int c;

  for ( i = 0; i < N; i++ ) {
    for ( j = 0; j < M; j++ ) {
      c = 0;
      for ( k = 0; k < K; k++ ) {
        c += A1[i][k]*A2[k][j];
      }
      if (A0[i*M+j] != c) {
        printf("FAILED at i:%d j:%d, got: %d expected: %d\n",i,j,A0[i*M+j],c);
        return -1;
      }
    }
  }

  printf("[PASSED]\n");

}

