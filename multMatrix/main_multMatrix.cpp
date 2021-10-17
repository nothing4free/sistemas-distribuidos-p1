#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix.h"

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;

}
int main()
{
    // crea un multiplicador de matrices nuevo
    multMatrix* mmatrix=new multMatrix();

    // crea matriz 1 aleatoria, dimensiones 5x5
    matrix_t* m1= mmatrix->createRandMatrix(5,5);

    // crea matriz 2 aleatoria, dimensiones 5x5
    matrix_t* m2= mmatrix->createIdentity(5,5);

    // crea la matriz resultado, que es el resultado de multiplicar m1 y m2 (dimensiones 5x5)
    matrix_t* mres=mmatrix->multMatrices(m1,m2);

    // escribe mres (matriz resultado) en el fichero "resultado.txt"
    mmatrix->writeMatrix(mres,"resultado.txt");

    // ahora crea una matriz 3, cuyos datos son leidos del fichero "resultado.txt"
    matrix_t* m3=mmatrix->readMatrix("resultado.txt");

    // multiplica matriz 1 y matriz 3, y almacena el resultado en matriz resultado 2
    matrix_t* mres2=mmatrix->multMatrices(m1,m3);

    // escribe mres2 (matriz resultado 2) en el fichero "resultado2.txt"
    mmatrix->writeMatrix(mres2,"resultado2.txt");


    // se libera la memoria de las matrices usadas
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete mmatrix;

}
