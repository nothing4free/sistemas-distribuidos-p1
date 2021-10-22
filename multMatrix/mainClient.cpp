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
    std::cout<<"ROW: "<<m->rows<<" COLS: "<<m->cols<<"\n";
    for(i=0;i<(m->rows*m->cols);++i);{
        std::cout<<"  " << m->data[i] << "  ";
        if(i%(m->rows)==0)
            std::cout<<"\n";
    }
    //std::cout<<"data[0] "<<m->data[0]<<" data[1]: "<<m->data[1]<<"\n";
}

int main(int argc,char** argv) {    

//TODO APLICAR VECTOR PARA QUE SEA DINÁMICO 

    multMatrixStub* matrixStub=new multMatrixStub();
    	// crea un multiplicador de matrices nuevo
    //multMatrix* mmatrix=new multMatrix();

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
    matrix_t* m1= matrixStub->createRandMatrix(5,5);
    std::cout<<"MATRIZ RANDOM RECIBIDA ["<<m1->data[0]<<","<<m1->data[1]<<"]\n";
    writeMat(m1);
    

    std::cout<<"CREANDO MATRIZ IDENTIDAD\n";
    matrix_t* m2= matrixStub->createIdentity(5,5);
    std::cout<<"MATRIZ IDENTIDAD RECIBIDA ["<<m2->data[0]<<","<<m2->data[1]<<"]\n";
    writeMat(m2);

    std::cout<<"MULTIPLICANDO MATRICES\n";
    matrix_t* mres=matrixStub->multMatrices(m1,m2);
    std::cout<<"MATRIZ MULTIPLICACION RECIBIDA ["<<mres->data[0]<<","<<mres->data[1]<<"]\n";
    writeMat(mres);
    
    std::cout<<"ESRIBIENDO MATRICES MRES y m2 EN 'resultado.txt' 'resultadoIden.txt'\n";
    matrixStub->writeMatrix(mres,"resultado.txt");
    matrixStub->writeMatrix(m2,"resultadoIden.txt");

    std::cout<<"LEYENDO MATRIZ\n";
    matrix_t* m3=matrixStub->readMatrix("resultado.txt");
    std::cout<<"LEYENDO MATRIZ ["<<m3->data[0]<<","<<m3->data[1]<<"]\n";
    writeMat(mres);

    std::cout<<"MULTIPLICNADO M1 CON M3(LEIDA)\n";
    matrix_t* mres2=matrixStub->multMatrices(m1,m3);
    writeMat(mres);
    
    std::cout<<"ESCRIBINEDO MRES2(MULT(M1.M3) en resultado2.txt)\n";
    matrixStub->writeMatrix(mres2,"resultado2.txt");
    writeMat(mres2);

    // se libera la memoria de las matrices usadas
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete matrixStub;

    std::cout<<"PROGRAMA TERMINADO\n";
	return 0;
}