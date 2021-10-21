#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix.h"
#include "multMatrixStub.h"

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;
}
void writeMat(matrix_t* m){
    int i=0;
    for(i=0;i<(m->rows*m->cols);++i);{
        std::cout<<"  " << m->data[i] << "  ";
        if(i%(m->rows)==0)
            std::cout<<"\n";
    }
}

int main(int argc,char** argv) {    

//TODO APLICAR VECTOR PARA QUE SEA DINÁMICO 

    multMatrixStub* matrixStub=new multMatrixStub();
    	// crea un multiplicador de matrices nuevo
    multMatrix* mmatrix=new multMatrix();

//EMPIEZA LA PRUEBA DE UN MENU
/*	matrix_t ** mat=new matrix_t*[10];
    int numMat=0;
    int i=0;
    
    

    std::cout << "Inicio del programa, que quiere hacer?\n";
   while (true)
   {
        std::cout << "1) Crear Matric Aleatoria 2-Matriz identidad 3-Multiplicar 4-Ver matrices creadas 5-Leer 6-Escribir \n";
        std::cin >> i;
        switch (i)
        {
        case 1: //RANDOM
            mat[numMat]=mmatrix->createRandMatrix(5,5);
            numMat++;
            break;
        case 2: //Identidad
            mat[numMat]=mmatrix->createIdentity(5,5);
            numMat++;
            break;
        case 3: //RANDOM
            int a=0,b=0;
            std::cout<<"Hay %d matrices creadas, cuales quieres multiplicar?(0-%d\n",numMat,numMat; 
            std::cout<<"Mat a: \n";
            std::cin>>a;
            std::cout<<"Mat b: \n";
            std::cin>>b;
            if((-1<a && a<=numMat )&&( -1<b && b<=numMat )){                 
                mat[numMat]=mmatrix->multMatrices(mat[a],mat[b]);
                numMat++;
            }else{
                std::cout <<"indice invalido\n";
            }
            
            
            break;
        case 4: //RANDOM
            mat[numMat]=mmatrix->createRandMatrix(5,5);
            break;
        case 5: //RANDOM
            mat[numMat]=mmatrix->createRandMatrix(5,5);
            break;
        case 6: //RANDOM
            mat[numMat]=mmatrix->createRandMatrix(5,5);
            break;
        default:
            std::cout<<"OPCION NO VALIDA\n";
            break;
        }
    }

*/
//TERMINA LA PRUEBA DE UN MENU

    std::cout<<"CREANDO MATRIZ\n";
    matrix_t* m1= mmatrix->createRandMatrix(5,5);
    std::cout<<"MATRIZ RANDOM RECIBIDA \n";
    writeMat(m1);
    
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
	return 0;
}