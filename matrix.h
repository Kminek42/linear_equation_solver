#ifndef MATRIX_
#define MATRIX_X

#define DEBUG

typedef double** matrix_t;
typedef double* vector_t;

int CreateMatrix( matrix_t * pTab, int nDim );

void DeleteMatrix( matrix_t * pTab, int nDim );

void TransMatrix( matrix_t pTab, int nDim );

void InverseMatrix( matrix_t pInv, matrix_t pTab, int nDim, double det );

double Det( matrix_t pTab, int nDim );

void LayoutEqu( matrix_t pInv, vector_t pB, vector_t pRes, int nDim );

void PrintMatrix( matrix_t pTab, int nDim );

#endif