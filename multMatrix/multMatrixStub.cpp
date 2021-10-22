// CLIENTE

#include "multMatrixStub.h"
#include <string.h>
#include "defineOperations.h"

/*
#define OP_OK             'O'
#define OP_EXIT           'E'

#define OP_READ           'R'
#define OP_MULT           'M'
#define OP_WRITE          'W'
#define OP_CREATEIDENTITY 'I'
#define OP_CREATERANDOM   'A' // "A" de aleatorio, era mas logico usar R para read.
*/


multMatrixStub::multMatrixStub() {
    char *ip = NULL;
    ip = new char[strlen(IP_SERVER) + 1];
    memcpy(ip, IP_SERVER, strlen(IP_SERVER) + 1);

    std::cout << "INICIANDO CLIENTE...\n";
    serverID = initClient(ip, PORT_SERVER);
    if(serverID == -1) { // manejo de errores
        std::cout << "ERROR EN CLIENTE: conexion no valida.\n";
        std::cout << " |--------------> Fichero: " <<__FILE__ << "\n";
        std::cout << " |--------------> Linea: " << __LINE__ << "\n";
    }  
    std::cout << "CONEXION CON SERVIDOR OK\n";
    delete ip;
}

multMatrixStub::~multMatrixStub() {
    char msg=OP_EXIT;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    char* buff = nullptr;
    int dataLen = 0;
    char state = 0;

    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&state, buff, sizeof(char));
    delete buff;

    if(state != OP_OK) {
        std::cout << "ERROR: fallo al cerrar conexion\n";
        std::cout << " |--------------> Fichero: " <<__FILE__ << "\n";
        std::cout << " |--------------> Linea: " << __LINE__ << "\n";
    }

    
}

// TO-DO: OPERACIONES CLIENTE

matrix_t* multMatrixStub::readMatrix(const char* filename) {
    char msg=OP_READ;
    int* buff = nullptr; // lectura de mensaje reci
    int dataLen = 0;
    
    matrix_t* resultado = new matrix_t;
    
    std::cout << "ENVIANDO EL TIPO DE OPERACION (readMatrix)\n";
    sendMSG(serverID, (void*)&msg, sizeof(char));


    std::cout << "ENVIANDO NOMBRE DE ARCHIVO (readMatrix)\n";
    sendMSG(serverID, (void*)filename, strlen(filename) + 1);
    std::cout << "RECIBIENDO EL RESULTADO (readMatrix)\n";
    recvMSG(serverID, (void**)&buff, &dataLen);

    std::cout << "COPIANDO MEMORIA\n";
    resultado->rows = buff[0];
    resultado->cols = buff[1];
    resultado->data=new int[resultado->rows*resultado->cols];
    memcpy(resultado->data, &buff[2], sizeof(int)*(resultado->rows*resultado->cols));
    //sin perdida de memoria y sin 
    std::cout << "RESULTADO: \n";
    std::cout << "Filas: %d Columnas: %d\n", resultado->rows, resultado->cols;
    delete buff;    //ahora funciona bien
    return resultado;
}

matrix_t* multMatrixStub::multMatrices(matrix_t* m1, matrix_t* m2) {

    char msg = OP_MULT;
    int dataLen = 0;
    
    matrix_t* resultado = new matrix_t;
    resultado->rows = m1->rows;
    resultado->cols = m2->cols;
    
    int tambuff=m1->cols*m1->rows+2;
    std::cout<<"Tamanio buff m1->cols*m1->rows+2 = "<<tambuff<<"\n";
    int *buff= new int[m1->cols*m1->rows+2]; 

    
    std::cout << "ENVIANDO EL TIPO DE OPERACION (multMatrix)\n";
    sendMSG(serverID, (void*)&msg, sizeof(char));
    
	buff[0]=m1->rows;
	buff[1]=m1->cols;
	for(int i=0;i<(m1->rows*m1->cols);++i){
		buff[i+2]=m1->data[i];
	}
    std::cout << "ENVIANDO MATRIZ 1 (multMatrix)\n";
    sendMSG(serverID, (void*)buff, sizeof(int)*m1->rows*m1->cols + 2*sizeof(int));
    delete buff;

    buff=new int [m2->rows*m2->cols+2]; //actualizamos tamanio
    std::cout << "ENVIANDO MATRIZ 2 (multMatrix)\n";
    buff[0] = m2->rows;
    buff[1] = m2->cols;
    for(int i=0;i<m2->cols*m2->rows;++i){
		buff[i+2]=m2->data[i];
	}
    sendMSG(serverID, (void*)buff, sizeof(int)*(m2->rows*m2->cols+2));
    
    //Matriz resultado
    std::cout << "ESPERANDO RESULTADO (multMatrix)\n";
    recvMSG(serverID, (void**)&resultado->data, &dataLen);
    std::cout << "RESULTADO RECIBIDO (multMatrix)\n";
    
    std::cout << "Devolviendo MATRIZ 2 (multMatrix)\n";
    
    return resultado;
}


void multMatrixStub::writeMatrix(matrix_t* m, const char *fileName) {
    char msg = OP_WRITE; 
    int* buff=new int[m->cols*m->rows +2];
        //TIPO OPE.
    sendMSG(serverID, (void*)&msg, sizeof(char));
        //NOMBRE ARCHIVO
        std::cout << "ENVIANDO fileName(wrtieMatrix)(multMatrix)\n";
    sendMSG(serverID, (void*)fileName, sizeof(fileName) + 1);
        //MATRIZ
    std::cout << "ENVIANDO MATRIZ (stub wrtieMAtrix)\n";
    buff[0] = m->rows;
    buff[1] = m->cols;
    for(int i=0;i<(m->rows*m->cols);++i){
		buff[i+2]=m->data[i];
	}
    sendMSG(serverID, (void*)buff, sizeof(int)*m->rows*m->cols + 2*sizeof(int));
    delete buff;
}

// precondicion: rows = cols
matrix_t* multMatrixStub::createIdentity(int rows, int cols) {
    int dataLen = 0;
    char msg = OP_CREATEIDENTITY;
    std::cout << "ENVIANDO OP_CREATID (stub)\n";
    sendMSG(serverID, (void*)&msg, sizeof(char));

    std::cout << "ENVIANDO ROWS, COLS (Stub createIdentity)\n";
    int aux[2] = {rows, cols};
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    matrix_t *identity = new matrix_t;
    identity->cols = cols;
    identity->rows = rows;
    
    recvMSG(serverID, (void**)&identity->data, &dataLen);
    return identity;
}

matrix_t* multMatrixStub::createRandMatrix(int rows, int cols) {
    int dataLen = 0;
    char msg = OP_CREATERANDOM;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int aux[2] = {rows, cols};
    sendMSG(serverID, (void*)aux, sizeof(int) * 2);

    matrix_t *randomMat = new matrix_t;
    randomMat->cols = cols;
    randomMat->rows = rows;
    
    recvMSG(serverID, (void**)&randomMat->data, &dataLen);

    return randomMat;
}  