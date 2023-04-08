#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "math.h"

int read_data( FILE* fin, matrix_t orig_matrix, vector_t b, int nDim );
int CreateVector( vector_t* pVec, int nSize );
void PrintVector( vector_t pVec, int nSize );

#define EPSILON (1e-200)

int main()
{

    int matrix_size = 0;
    FILE* pFile = fopen( "../input.txt", "r" );
    if( !pFile ) { printf( "\nfile open error\n" ); return -2; }
    fscanf( pFile, "%d", &matrix_size );

#ifdef DEBUG
    printf( "Matrix size: %d\n\n", matrix_size );
#endif


    vector_t b = NULL;
    if( !CreateVector( &b, matrix_size ) )
    {
        printf( "b vector creation error\n" ); return -3;
    }

    matrix_t orig_matrix = NULL;
    if( !CreateMatrix( &orig_matrix, matrix_size ) )
    {
        printf( "Main matrix creation error\n" ); return -4;
    }

    if( !read_data( pFile, orig_matrix, b, matrix_size ) )
    {
        printf( "file read error" );
        return -5;
    }

#ifdef DEBUG
    printf( "Original matrix:\n" );
	PrintMatrix( orig_matrix, matrix_size );

	printf( "\nb vector: \n" );
	PrintVector( b, matrix_size );
#endif

    matrix_t inv_matrix = NULL;
    if( !CreateMatrix( &inv_matrix, matrix_size ) )
    {
        printf( "Second matrix creation error\n" ); return -6;
    }

    double det = Det( orig_matrix, matrix_size );

#ifdef DEBUG
    printf( "\ndet = %f\n", det );
#endif

    if( fabs( det ) < EPSILON )
    {
        printf( "error: det = 0\n" );
        return -7;
    }

    InverseMatrix( inv_matrix, orig_matrix, matrix_size, det );
#ifdef DEBUG
    printf( "\nInverse matrix: \n" );
	PrintMatrix( inv_matrix, matrix_size );
#endif

    vector_t res = NULL;
    if( !CreateVector( &res, matrix_size ) )
    {
        printf( "Res vector creation error\n" ); return -8;
    }

    LayoutEqu( inv_matrix, b, res, matrix_size );
    for( int i = 0; i < matrix_size; i++ )
        printf( "x%d = %lf\n", i, res[i] );

    DeleteMatrix( &orig_matrix, matrix_size );
    DeleteMatrix( &inv_matrix, matrix_size );
    free( b );
    free( res );
    return 0;
}

int read_data( FILE* fin, matrix_t orig_matrix, vector_t b, int nDim )
{
    for( int i = 0; i < nDim; i++, orig_matrix++ )
    {
        vector_t temp_v = *orig_matrix;
        for( int j = 0; j < nDim; j++ )
            if( !fscanf( fin, "%lf", temp_v++ ) ) return 0;
        if( !fscanf( fin, "%lf", b++ ) ) return 0;
    }
    return 1;
}

int CreateVector( vector_t* pVec, int nSize )
{
    *pVec = (vector_t)malloc( nSize * sizeof( double ) );
    if ( !pVec ) return 0;
    memset( *pVec, 0, nSize * sizeof( double ) );
    return 1;
}

void PrintVector( vector_t pVec, int nSize )
{
    for( int i = 0; i < nSize; i++, pVec++ ) printf( "%f\t", *pVec );
    printf( "\n" );
}
