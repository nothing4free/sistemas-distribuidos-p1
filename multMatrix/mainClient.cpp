#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "multmatrix.h"
#include "multMatrixStub.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;

//Falta aumentar dinamicamente el tamaño del array de matrix_t y revisar el menu

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;
}
void writeMat(matrix_t* m){
    int i=0;
    cout<<"ROW: "<<m->rows<<" COLS: "<<m->cols<<"\n";
    cout<<"data[0] "<<m->data[0]<<" data[1]: "<<m->data[1]<<"\n";
}

/**
 * @brief muestra las dimensiones de todas las matrices alamcenadas y los 2 primeros elementos
 * @param vect El vector que almacena los punteros de las matrices
*/
void mostrarPosiblesMatrices(vector<matrix_t*> &vect){ //referencia a un vector de direcciones de matrices
    printf("Matrices Disponibles(%lu)\n",vect.size());
    for (auto i = 0; i < vect.size(); i++)
    {
        printf("MAT: %d \n\tCol: %d Row: %d [0] = %d [1] = %d\n",i,vect[i]->rows,vect[i]->cols,vect[i]->data[0],vect[i]->data[1]);
    }
}
// ALGO VA MAL CON ESTA FUNCION
//**
//* @brief devulve true si a está entre [0 y numMax)
//*/
//bool checkInd(long unsigned int a,long unsigned int numMax){ 
//    return (-1<a && a<numMax);
//}

int main(int argc,char** argv) {    

//TODO APLICAR VECTOR PARA QUE SEA DINÁMICO 

    multMatrixStub* matrixStub=new multMatrixStub();
    	// crea un multiplicador de matrices nuevo
    multMatrix* matrixInOut=new multMatrix();

//EMPIEZA LA PRUEBA DE UN MENU
    vector<matrix_t*> mat_vec;

    int i=0;

    char fileName[20];
    std::cout << "Inicio del programa, que quiere hacer?\n";
   while (i!=8)
   {
        std::cout << "1) Crear Matriz Aleatoria 2-Matriz identidad 3-Multiplicar 4-Leer de Fichero 5-Escribir Fichero 6-Leer terminal 7-Mostrar matrices 8-Salir\n";
        std::cin >> i;
        switch (i)
        {
            
        case 1: //RANDOM
            {
            int r,c;
            
            cout<<"Rows: \n";
            cin>>r;
            cout<<"Cols: \n";
            cin>>c;
            
            mat_vec.push_back(matrixStub->createRandMatrix(r,c));
            }
            break;
        case 2: //Identidad
            {
            int r,c;
            
            cout<<"Rows: \n";
            cin>>r;
            cout<<"Cols: \n";
            cin>>c;
            
            mat_vec.push_back(matrixStub->createIdentity(r,c));
            }  
            break;
        case 3: //Multiplicar 2
            {
                long unsigned int a=0,b=0;
                printf("Que 2 matrices quieres multiplicar?\n");
                mostrarPosiblesMatrices(mat_vec);

                std::cout<<"Introduce el numero de la PRIMERA matriz: \n";
                std::cin>>a;
                std::cout<<"Introduce el numero de la SEGUNDA matriz: \n";
                std::cin>>b;

                /*if (!(checkInd(a,mat_vec.size())&&checkInd(b,mat_vec.size())))//si no cumple que está dentro del índice
                {
                    std::cout <<"indice invalido\n";
                    break;
                } */      
                if(a<0||mat_vec.size()<=a){
                    cout<<"primera matriz fuera de rango";
                }else if (b<0||mat_vec.size()<=b)
                {
                    cout<<"segunda matriz fuera de rango";
                }
                else
                {
                    mat_vec.push_back(matrixStub->multMatrices(mat_vec[a],mat_vec[b]));
                }
                

                   
            }
            break;
        case 4: //READ FILE
            
            std::cout<<"introduzca nombre de archivo PARA LEER\n";
            std::cin>>fileName;
            mat_vec.push_back(matrixInOut->readMatrix(fileName));
            break;
        case 5: //WRITE
            {
                long unsigned choice=0;

                std::cout<<"introduzca nombre de archivo PARA Escribir\n";
                std::cin>>fileName;
                
                cout<<"Que matriz quiere guardar?\n";
                mostrarPosiblesMatrices(mat_vec);
                std::cin>>choice;
                
                if(choice<0||mat_vec.size()<=choice)
                    cout<<"primera matriz fuera de rango";
                else
                    matrixInOut->writeMatrix(mat_vec[choice],fileName);
                
                
               
            }
            break;
        case 6: //Lectura terminal (QUEDAAAAAAA)
            {   
                cout<<"Lectura por terminal\n";

                matrix_t * lectura= new matrix_t; //Probablemente de error a la hora de eliminarlo
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
                mat_vec.push_back(lectura);
            }
            break;
        case 7: //Mostrar matrices credas
            mostrarPosiblesMatrices(mat_vec);
            break;
        case 8: //Salida
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
    */
    for (auto p : mat_vec)
    {
        delete p;
    }
    mat_vec.clear();
    delete matrixStub;
    delete matrixInOut;
    std::cout<<"PROGRAMA TERMINADO\n";
	return 0;
}