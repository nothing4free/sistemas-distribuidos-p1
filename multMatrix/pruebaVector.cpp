#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "multmatrix.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;

void mostrarPosiblesMatrices(vector<matrix_t*> &vect){ //referencia a un vector de direcciones de matrices
    printf("Matrices Disponibles(%lu)\n",vect.size());
    for (auto i = 0; i < vect.size(); i++)
    {
        printf("MAT: %d \n\tCol: %d Row: %d [0] = %d [1] = %d\n",i,vect[i]->rows,vect[i]->cols,vect[i]->data[0],vect[i]->data[1]);
    }
}

int main(int argc, char const *argv[])
{
    vector<matrix_t*> mat_vec;
    multMatrix* matrixInOut=new multMatrix();
    mat_vec.push_back(matrixInOut->createIdentity(2,2));
    mat_vec.push_back(matrixInOut->createRandMatrix(2,2));
    printf("MAT1:\n\tROWS: %d COLS: %d [0][0]: %d\n",mat_vec[0]->rows,mat_vec[0]->cols,mat_vec[0]->data[0]);
    mostrarPosiblesMatrices(mat_vec);
    return 0;
}
