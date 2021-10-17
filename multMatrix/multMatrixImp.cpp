// SERVIDOR
#include "multMatrixImp.h"

#define OP_READ           'R'
#define OP_MULT           'M'
#define OP_WRITE          'W'
#define OP_CREATEIDENTITY 'I'
#define OP_CREATERANDOM   'A' // "A" de aleatorio, era mas logico usar R para read.

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

                } break ;
                
                case OP_MULT: {

                } break;

                case OP_WRITE: {

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