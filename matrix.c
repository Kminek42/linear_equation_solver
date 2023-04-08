#include "matrix.h"
#include "stdlib.h"
#include "memory.h"
#include "stdio.h"


void Complement( matrix_t pTabO, matrix_t pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( matrix_t pTabD, matrix_t pTab, int nDim );

int CreateMatrix( matrix_t* pTab, int nDim )
{
    *pTab = (vector_t*)malloc( nDim * sizeof( vector_t ) );
    if( *pTab == NULL ) return 0;
    memset( *pTab, 0, nDim * sizeof( vector_t ) );
    vector_t* temp_vector = *pTab;
    for( int i = 0; i < nDim; i++ )
    {
        *temp_vector = (vector_t)malloc( nDim * sizeof( double ) );
        if( *temp_vector == NULL ) return 0;
        memset( *temp_vector, 0, nDim * sizeof( double ) );
        temp_vector++;
    }
    return 1;
}

void TransMatrix( matrix_t pTab, int nDim )
{
    vector_t* temp_v1 = pTab;
    for( int i = 0; i < nDim - 1; i++, temp_v1++ )
    {
        vector_t temp_v2 = *temp_v1 + i + 1;
        for( int j = i + 1; j < nDim; j++ )
        {
            double temp = *temp_v2;
            *temp_v2++ = pTab[j][i];
            pTab[j][i] = temp;
        }
    }
}

void InverseMatrix( matrix_t pInv, matrix_t pTab, int nDim, double det )
{

    ComplMatrix( pInv, pTab, nDim );
#ifdef DEBUG
    printf( "\nComplMatrix:\n" );
	PrintMatrix( pInv, nDim );
#endif

    TransMatrix( pInv, nDim );
#ifdef DEBUG
    printf( "\nTransMatrix:\n" );
	PrintMatrix( pInv, nDim );
#endif

    vector_t* temp_vector1 = pInv;
    for( int i = 0; i < nDim; i++, temp_vector1++ )
    {
        vector_t temp_vector2 = *temp_vector1;
        for( int j = 0; j < nDim; j++, temp_vector2++ ) *temp_vector2 /= det;
    }
}

double Det( matrix_t pTab, int nDim )
{
    if( nDim == 1 ) return **pTab;
    if( nDim == 2 ) return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];

    matrix_t temp_matrix;
    if( !CreateMatrix( &temp_matrix, nDim - 1 ) )
    {
        printf( "\ncreate matrix error\n" );
        return 0;
    }

    double sum = 0.0;
    int sign = 1;
    vector_t temp_vector = *pTab;
    for( int i = 0; i < nDim; i++, temp_vector++ )
    {
        Complement( temp_matrix, pTab, 0, i, nDim );
        sum += sign * *temp_vector * Det( temp_matrix, nDim - 1 );
        sign = -sign;
    }
    DeleteMatrix( &temp_matrix, nDim - 1 );
    return sum;
}

void Complement( matrix_t pTabO, matrix_t pTabI, int nRow, int nCol, int nDim )
{
    for( int i = 0; i < nDim; i++, pTabI++ )
    {
        if( i == nRow ) continue;
        vector_t temp_vector1 = *pTabO++;
        vector_t temp_vector2 = *pTabI;

        for( int j = 0; j < nDim; j++, temp_vector2++ )
        {
            if( nCol == j ) continue;
            *temp_vector1++ = *temp_vector2;
        }
    }
}

void ComplMatrix( matrix_t pTabD, matrix_t pTab, int nDim )
{
    matrix_t temp_matrix = NULL;
    if( !CreateMatrix( &temp_matrix, nDim - 1 ) )
    {
        printf( "\ncreate compl matrix error\n" );
        return;
    }

    vector_t* temp_vector1 = pTabD;
    int sign = 1;
    for( int i = 0; i < nDim; i++ )
    {
        vector_t temp_vector2 = *temp_vector1++;
        for( int j = 0; j < nDim; j++ )
        {
            Complement( temp_matrix, pTab, i, j, nDim );
            *temp_vector2++ = sign * Det( temp_matrix, nDim - 1 );
            sign = -sign;
        }
        sign = -sign;
    }
}

void LayoutEqu( matrix_t pInv, vector_t pB, vector_t pRes, int nDim )
{
    for( int i = 0; i < nDim; i++, pRes++ )
    {
        vector_t p = *pInv++;
        vector_t pTemp = pB;
        for( int j = 0; j < nDim; j++, p++, pTemp++ )
        {
            *pRes += *p * *pTemp;
        }
    }
}

void PrintMatrix( matrix_t pTab, int nDim )
{
    printf( "\n--------------------------------\n\n" );
    for( int i = 0; i < nDim; i++, pTab++ )
    {
        double* temp_tab = *pTab;
        for( int j = 0; j < nDim; j++, temp_tab++ )
            printf( "%.5f\t\t", *temp_tab );
        printf( "\n\n" );
    }
    printf( "--------------------------------\n" );
}

void DeleteMatrix( matrix_t* pTab, int nDim )
{

    vector_t* p = *pTab;

    for( int i = 0; i < nDim; i++ )
    {
        free( *p++ );
    }
    free( *pTab );

    *pTab = NULL;

}
