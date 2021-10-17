// SERVIDOR
#include "multMatrixImp.h"
#include "multmatrix.h"

#define OP_READ           'R'
#define OP_MULT           'M'
#define OP_WRITE          'W'
#define OP_CREATEIDENTITY 'I'
#define OP_CREATERANDOM   'A' // "A" de aleatorio, era mas logico usar R para read.

// NOTA: adminMatrices es el equivalente a "ops" en la practica 0. Es el objeto que se encarga
// de hacer cosas con las matrices.


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
					//recibir datos
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
					sendMSG(clientID, (void*)&aux, sizeof(int) * mat->cols * mat->rows + 2*sizeof(int));
					delete aux;
					delete fileName;
					delete mat;
                } break ;
                
                case OP_MULT: {
                    //se puede optimizar para que solo haya 1 mensaje 
					//pero dolor cerebral son las 3 quiero dormir
					matrix_t* matA=nullptr;
					matrix_t* matB=nullptr;
					matrix_t* res=nullptr;

					recvMSG(clientID,(void**)&matA->data,&dataLen); //2 matrices con tamanio
					matA->rows=matA->data[0];
					matA->cols=matA->data[1];
					matA->data=&(matA->data[2]);
					std::cout << "RECIBIDA MATRIZ A\n";
					std::cout << "ROWS: %d COLS: %d\n", matA->rows, matA->cols;

					recvMSG(clientID,(void**)&matB->data,&dataLen); //2 matrices con tamanio
					matB->rows=matB->data[0];
					matB->cols=matB->data[1];
					matB->data=&(matB->data[2]);
					std::cout << "RECIBIDA MATRIZ B\n";
					std::cout << "ROWS: %d COLS: %d\n", matB->rows, matB->cols;


						//operamos
					res= adminMatrices->multMatrices(matA,matB); 
						//enviamos resultado de vuelta el ya puede saber como será la matriz 
						//al tener los tam de las que nos envio
					sendMSG(clientID,(void*)&res->data,sizeof(int)*matA->rows*matB->cols);
					delete matA;
					delete matB;
					delete res;
                } break;

                case OP_WRITE: { //TODO -> rehacer para recibir de la nueva forma
                    //recibire 2 mensajes, 1 con el nombre otro con la matriz
					char *fileName=nullptr;
					matrix_t* mat=nullptr;

					recvMSG(clientID,(void**)&fileName,&dataLen);
					//utilizo mat.data como buffer, 
					//despues de actualizar col y row, reseteo la posicion de mat.data
					recvMSG(clientID,(void**)&mat->data,&dataLen);
					mat->rows=mat->data[0];
					mat->cols=mat->data[1];
					mat->data=&(mat->data[2]);
					delete fileName;
					delete mat;
                } break;

                case OP_CREATEIDENTITY: {

                    int row = 0, col = 0;
                    matrix_t* res = nullptr; // se crea la matriz resultado, q de momento es null
                    
                    // recibes cosas (creo q es innecesario porque ya se reciben antes del switch?)
                    recvMSG(clientID, (void**)&msg, &dataLen);
                    memcpy(&row,msg,sizeof(int));
					memcpy(&col,msg+sizeof(int),sizeof(int));
					delete msg;
                    
					res=adminMatrices->createIdentity(row,col); // creas matriz identidad...
					sendMSG(clientID,(void*)&res->data,sizeof(int)*row*col); //... y la envias de vuelta
					delete res;

                } break;

                case OP_CREATERANDOM: {
                    int row = 0, col = 0;
					matrix_t* res=nullptr;
					//recibir operandos
					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&row,msg,sizeof(int));
					memcpy(&col,msg+sizeof(int),sizeof(int));
					delete msg;
					//operar
					res = adminMatrices->createRandMatrix(row,col);
					//devolver resultado, el sabrá el tamaño porque lo ha pedido XD 
					sendMSG(clientID,(void*)&res->data,sizeof(int)*row*col);
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