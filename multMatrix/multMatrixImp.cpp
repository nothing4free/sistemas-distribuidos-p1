// SERVIDOR

#include "defineOperations.h"
#include "multMatrixImp.h"
#include "multmatrix.h"

void writeMat(matrix_t* m){
    int i=0;
    for(i=0;i<(m->rows*m->cols);++i);{
        std::cout<<"  " << m->data[i] << "  ";
        if(i%(m->rows)==0)
            std::cout<<"\n";
    }
}

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

                    char *fileName=nullptr; //se inicializa en el primer recvMSG linea 52
					matrix_t* mat = new matrix_t;
					int * aux=nullptr;
					std::cout<<"OP_READ->matrixImp\n";
						//recibir nombre fichero a leer
					recvMSG(clientID,(void**)&fileName,&dataLen);					
					mat = adminMatrices->readMatrix(fileName);
					writeMat(mat);
						//formatear adecuadamente 
					//2 primeros son la fila y columnas luego la data
					aux= new int[mat->cols*mat->rows+2];
					aux[0]=mat->rows;
					aux[1]=mat->cols;
					for(int i=0;i<dataLen;++i){
						aux[i+2]=mat->data[i];
					}
						//devolver resultado
					sendMSG(clientID, (void*)aux, sizeof(int)*(mat->cols * mat->rows +2));
					delete aux;
					delete fileName;
					delete mat;
                } break ;
                
                case OP_MULT: {
					int* buff = nullptr;
                    //se puede optimizar para que solo haya 1 mensaje 
					//pero dolor cerebral son las 3 quiero morir
					matrix_t* matA=new matrix_t;
					matrix_t* matB=new matrix_t;
					matrix_t* res=nullptr;

					std::cout<<"OP_MULT\n";
						//recibir mat A
					recvMSG(clientID,(void**)&buff,&dataLen); //2 matrices con tamanio
					matA->rows=buff[0];
					matA->cols=buff[1];
					matA->data= new int[matA->rows*matA->cols];
					memcpy(matA->data, &buff[2], sizeof(int)*(dataLen-2));
					std::cout << "RECIBIDA MATRIZ A\nCols: "<<matA->cols;
					std::cout << "ROWS: "<<matA->rows<<" COLS: "<<matA->cols<<" [0][0]: "<<matA->data[0]<<"\n";
					delete buff;

						//recibir mat B
					recvMSG(clientID,(void**)&buff,&dataLen); //2 matrices con tamanio
					
					matB->rows=buff[0];
					matB->cols=buff[1];
					matB->data= new int[matB->rows*matB->cols];
					memcpy(matB->data, &buff[2], sizeof(int)*(dataLen-2));
					std::cout << "RECIBIDA MATRIZ B\n";
					std::cout << "ROWS: "<<matB->rows<<" COLS: "<<matB->cols<<" [0][0]: "<<matB->data[0]<<"\n";
					delete buff;

						//operamos
					res= adminMatrices->multMatrices(matA,matB); 
						//enviamos resultado de vuelta el ya puede saber como será la matriz 
						//al tener los tam de las que nos envio
					sendMSG(clientID,(void*)res->data,sizeof(int)*matA->rows*matB->cols);
					delete matA;
					delete matB;
					delete res;
                } break;

                case OP_WRITE: { 
					char *fileName=nullptr;
					int *buff=nullptr;
					matrix_t* mat=new matrix_t;

				        //NOMBRE ARCHIVO
					recvMSG(clientID,(void**)&fileName,&dataLen);
						//RECIBIR DATA
					recvMSG(clientID,(void**)&buff,&dataLen);
					mat->rows=buff[0];
					mat->cols=buff[1];
					mat->data= new int[mat->rows*mat->cols];
					memcpy(mat->data, &buff[2], sizeof(int)*(dataLen-2));
						//ESCRIBIR COMO TAL
					adminMatrices->writeMatrix(mat,fileName);

					delete fileName;
					delete mat;
					delete buff;
                } break;

                case OP_CREATEIDENTITY: {
					int *dimensiones=nullptr;
                    matrix_t* res = new matrix_t;
                    	//DIMENSIONES DE LA MATRIZ
                    recvMSG(clientID, (void**)&dimensiones, &dataLen);
						//CREAR Y DEVOLVER
					res=adminMatrices->createIdentity(dimensiones[0],dimensiones[1]);
					sendMSG(clientID,(void*)res->data,sizeof(int)* res->rows *res->cols);
					delete dimensiones;
					delete res;
                } break;

                case OP_CREATERANDOM: {
                    int *dimensiones=nullptr;
                    matrix_t* res = new matrix_t;
                    	//DIMENSIONES DE LA MATRIZ
                    recvMSG(clientID, (void**)&dimensiones, &dataLen);
						//CREAR Y DEVOLVER
					res=adminMatrices->createRandMatrix(dimensiones[0],dimensiones[1]);
					sendMSG(clientID,(void*)res->data,sizeof(int)* res->rows *res->cols);
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