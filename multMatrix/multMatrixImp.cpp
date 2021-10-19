// SERVIDOR

#include "defineOperations.h"
#include "multMatrixImp.h"
#include "multmatrix.h"
/*
#define OP_READ           'R'
#define OP_MULT           'M'
#define OP_WRITE          'W'
#define OP_CREATEIDENTITY 'I'
#define OP_CREATERANDOM   'A' // "A" de aleatorio, era mas logico usar R para read.

// NOTA: adminMatrices es el equivalente a "ops" en la practica 0. Es el objeto que se encarga
// de hacer cosas con las matrices.
*/

multMatrixImp::multMatrixImp(int clientID) {
    adminMatrices = new multMatrix();
    exitFlag = false;
    this->clientID = clientID;
}

multMatrixImp::~multMatrixImp() {
    delete adminMatrices;
    closeConnection(clientID);
}

void multMatrixImp::exec() {
    while(!exitFlag) {
        char* msg = NULL;
        int dataLen = 0;
        char tipo_op = -1;

        recvMSG(clientID, (void**)&msg, &dataLen);

        if(dataLen == -1) { // maneja errores
            std::cout << "ERROR EN SERVIDOR: no hay datos.\n";
            std::cout << " |--------------> Fichero: " <<__FILE__ << "\n";
            std::cout << " |--------------> Linea: " << __LINE__ << "\n";
        } else { // do stuff
            tipo_op = msg[0];
            delete msg;

            // TO-DO: operaciones
            switch(tipo_op) {
                case OP_READ: {

                    char *fileName=nullptr;
					matrix_t* mat = nullptr;
					int * aux=nullptr;
					
						//recibir nombre fichero a leer
					recvMSG(clientID,(void**)&fileName,&dataLen);					
					mat = adminMatrices->readMatrix(fileName);
						//formatear adecuadamente 
					//2 primeros son la fila y columnas luego la data
					aux= new int[mat->cols*mat->rows+2];
					aux[0]=mat->rows;
					aux[1]=mat->cols;
					for(int i=0;i<dataLen;++i){
						aux[i+2]=mat->data[i];
					}
						//devolver resultado
					sendMSG(clientID, (void*)&aux, sizeof(int)*(mat->cols * mat->rows +2));
					delete aux;
					delete fileName;
					delete mat;
                } break ;
                
                case OP_MULT: {
					int* buff = nullptr;
                    //se puede optimizar para que solo haya 1 mensaje 
					//pero dolor cerebral son las 3 quiero morir
					matrix_t* matA=nullptr;
					matrix_t* matB=nullptr;
					matrix_t* res=nullptr;

						//recibir mat A
					recvMSG(clientID,(void**)&buff,&dataLen); //2 matrices con tamanio
					matA->rows=buff[0];
					matA->cols=buff[1];
					memcpy(&matA, &buff[2], sizeof(int)*(dataLen-2));
					std::cout << "RECIBIDA MATRIZ A\n";
					std::cout << "ROWS: %d COLS: %d [0][0]:%d\n", matA->rows, matA->cols,matA->data[0];
					delete buff;

						//recibir mat B
					recvMSG(clientID,(void**)&buff,&dataLen); //2 matrices con tamanio
					matB->rows=buff[0];
					matB->cols=buff[1];
					memcpy(&matB, &buff[2], sizeof(int)*(dataLen-2));
					std::cout << "RECIBIDA MATRIZ B\n";
					std::cout << "ROWS: %d COLS: %d [0][0]\n", matB->rows, matB->cols, matB->data[0];
					delete buff;

						//operamos
					res= adminMatrices->multMatrices(matA,matB); 
						//enviamos resultado de vuelta el ya puede saber como será la matriz 
						//al tener los tam de las que nos envio
					sendMSG(clientID,(void*)&res->data,sizeof(int)*matA->rows*matB->cols);
					delete matA;
					delete matB;
					delete res;
                } break;

                case OP_WRITE: { 
					char *fileName=nullptr;
					int *buff=nullptr;
					matrix_t* mat=nullptr;

				        //NOMBRE ARCHIVO
					recvMSG(clientID,(void**)&fileName,&dataLen);
						//RECIBIR DATA
					recvMSG(clientID,(void**)&buff,&dataLen);
					mat->rows=buff[0];
					mat->cols=buff[1];
					memcpy(&mat, &buff[2], sizeof(int)*(dataLen-2));
						//ESCRIBIR COMO TAL
					adminMatrices->writeMatrix(mat,fileName);

					delete fileName;
					delete mat;
					delete buff;
                } break;

                case OP_CREATEIDENTITY: {
					int *dimensiones=nullptr;
                    matrix_t* res = nullptr;
                    	//DIMENSIONES DE LA MATRIZ
                    recvMSG(clientID, (void**)&dimensiones, &dataLen);
						//CREAR Y DEVOLVER
					res=adminMatrices->createIdentity(dimensiones[0],dimensiones[1]);
					sendMSG(clientID,(void*)&res->data,sizeof(int)* res->rows *res->cols);
					delete dimensiones;
					delete res;
                } break;

                case OP_CREATERANDOM: {
                    int *dimensiones=nullptr;
                    matrix_t* res = nullptr;
                    	//DIMENSIONES DE LA MATRIZ
                    recvMSG(clientID, (void**)&dimensiones, &dataLen);
						//CREAR Y DEVOLVER
					res=adminMatrices->createRandMatrix(dimensiones[0],dimensiones[1]);
					sendMSG(clientID,(void*)&res->data,sizeof(int)* res->rows *res->cols);
					delete dimensiones;
					delete res;
                } break;

                default:
                    std::cout << "ERROR EN SERVIDOR: tipo de operacion no valido\n";
                    std::cout << " |--------------> Fichero: " <<__FILE__ << "\n";
                    std::cout << " |--------------> Linea: " << __LINE__ << "\n";
                break;
            }
        }
    }
}