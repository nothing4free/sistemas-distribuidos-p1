#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix.h"
#include "multMatrixStub.h"

//Falta aumentar dinamicamente el tamaño del array de matrix_t y revisar el menu

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;
}
void writeMat(matrix_t* m){
    int i=0;
    std::cout<<"ROW: "<<m->rows<<" COLS: "<<m->cols<<"\n";
    for(int i=0;i<m->rows*m->cols;i++)
     {
         if(i%m->rows==0){
            printf("\n");
         }
        
        printf(" %d\n",m->data[i]);
        
     }
    std::cout<<"\n";
    //std::cout<<"data[0] "<<m->data[0]<<" data[1]: "<<m->data[1]<<"\n";
}
void mostrarPosiblesMatrices(matrix_t** mat,int numMat){
    printf("Matrices Disponibles(%d)",numMat);
    for (int i = 0; i < numMat; i++)
    {
        printf("MAT: %d [0][0] = %d\n",i,mat[i]->data[0]);
    }
}
bool checkInd(int a,int numMat){
    return (-1<a&&a<numMat);
}

int main(int argc,char** argv) {    

//TODO APLICAR VECTOR PARA QUE SEA DINÁMICO 

    multMatrixStub* matrixStub=new multMatrixStub();
    	// crea un multiplicador de matrices nuevo
    multMatrix* matrixInOut=new multMatrix();

//EMPIEZA LA PRUEBA DE UN MENU
	matrix_t ** mat=new matrix_t*[10];
    int numMat=0;
    int tamMat=10;

    int i=0;

    char fileName[20];
    std::cout << "Inicio del programa, que quiere hacer?\n";
   while (i!=7)
   {
        std::cout << "1) Crear Matric Aleatoria 2-Matriz identidad 3-Multiplicar 4-Leer de Fichero 5-Escribir 6-Leer terminal 7-Salir\n";
        std::cin >> i;
        switch (i)
        {
            
        case 1: //RANDOM
            mat[numMat]=matrixStub->createRandMatrix(5,5);
            numMat++;
            break;
        case 2: //Identidad
            mat[numMat]=matrixStub->createIdentity(5,5);
            numMat++;
            break;
        case 3: //Multiplicar 2
            {
                int a=0,b=0;
                printf("Que 2 matrices quieres multiplicar?\n");
                mostrarPosiblesMatrices(mat,numMat);

                std::cout<<"Mat a: \n";
                std::cin>>a;
                std::cout<<"Mat b: \n";
                std::cin>>b;
                if (!(checkInd(a,numMat)&&checkInd(b,numMat)))//si no cumple que está dentro del índice
                {
                    std::cout <<"indice invalido\n";
                    break;
                }             
                mat[numMat]=matrixStub->multMatrices(mat[a],mat[b]);
                numMat++;
            }
            break;
        case 4: //READ FILE
            
            std::cout<<"introduzca nombre de archivo PARA LEER\n";
            std::cin>>fileName;
            mat[numMat]=matrixInOut->readMatrix(fileName);
            break;
        case 5: //WRITE
            {
                int choice=0;
                std::cout<<"introduzca nombre de archivo PARA LEER\n";
                std::cin>>fileName;
                
                mostrarPosiblesMatrices(mat,numMat);
                std::cin>>choice;
                matrixInOut->writeMatrix(mat[choice],fileName);
            }
            break;
        case 6: //Lectura terminal
            {   
                matrix_t * lectura= new matrix_t;
                std::cout<<"Filas: \n";
                std::cin>>lectura->rows;
                std::cout<<"Columnas: \n";
                std::cin>>lectura->cols;
                lectura->data=new int [lectura->rows*lectura->cols];
                for (int i = 0; i < lectura->rows*lectura->cols; i++)
                {
                    printf("Siguiente valor (%d)",i);
                    std::cin>>lectura->data[i];
                }
                
                mat[numMat]=lectura;
                numMat++;
            }
            break;
        case 7: //Salida
            break;
        default:
            std::cout<<"OPCION NO VALIDA\n";
            break;
        }
    }


//TERMINA LA PRUEBA DE UN MENU
/*
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
    matrixInOut->writeMatrix(mres,"resultado.txt");
    matrixInOut->writeMatrix(m2,"resultadoIden.txt");

    std::cout<<"LEYENDO MATRIZ\n";
    matrix_t* m3=matrixInOut->readMatrix("resultado.txt");
    std::cout<<"LEYENDO MATRIZ ["<<m3->data[0]<<","<<m3->data[1]<<"]\n";
    writeMat(mres);

    std::cout<<"MULTIPLICNADO M1 CON M3(LEIDA)\n";
    matrix_t* mres2=matrixStub->multMatrices(m1,m3);
    writeMat(mres);
    
    std::cout<<"ESCRIBINEDO MRES2(MULT(M1.M3) en resultado2.txt)\n";
    matrixInOut->writeMatrix(mres2,"resultado2.txt");
    writeMat(mres2);

    // se libera la memoria de las matrices usadas
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete matrixStub;
    delete matrixInOut;
    std::cout<<"PROGRAMA TERMINADO\n";*/
	return 0;
}