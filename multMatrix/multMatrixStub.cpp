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

    recvMSG(serverID, (void**)buff, &dataLen);
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
    int* buff = nullptr; // cha cha real smooth ahora es un int
    int dataLen = 0;

    matrix_t* resultado = nullptr;
    std::cout << "ENVIANDO EL TIPO DE OPERACION (readMatrix)\n";
    sendMSG(serverID, (void*)&msg, sizeof(char));
    std::cout << "ENVIANDO NOMBRE DE ARCHIVO (readMatrix)\n";
    sendMSG(serverID, (void*)&filename, strlen(filename) + 1);
    std::cout << "RECIBIENDO EL RESULTADO (readMatrix)\n";
    recvMSG(serverID, (void**)&buff, &dataLen);

    std::cout << "COPIANDO MEMORIA\n";
    resultado->rows = buff[0];
    resultado->cols = buff[1];
    memcpy(&resultado, &buff[2], sizeof(int)*(dataLen-2));
    //sin perdida de memoria y sin 
    std::cout << "RESULTADO: \n";
    std::cout << "Filas: %d Columnas: %d\n", resultado->rows, resultado->cols;
    delete buff;    //ahora funciona bien
    return resultado;
}

matrix_t* multMatrixStub::multMatrices(matrix_t* m1, matrix_t* m2) {


    int dataLen = 0;
    matrix_t* resultado = nullptr;
    resultado->cols = m2->cols;
    resultado->rows = m1->rows;
    char msg = OP_MULT;

    std::cout << "ENVIANDO EL TIPO DE OPERACION (multMatrix)\n";
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int aux[2] = {m1->rows, m1->cols};
    std::cout << "ENVIANDO ROWS Y COLS MAT1 (multMatrix)\n";
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    std::cout << "ENVIANDO MATRIZ 1 (multMatrix)\n";
    sendMSG(serverID, (void*)&m1->data, sizeof(int)*m1->rows*m1->cols);

    aux[0] = m2->rows;
    aux[1] = m2->cols;
    std::cout << "ENVIANDO ROWS Y COLS MAT2 (multMatrix)\n";
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    std::cout << "ENVIANDO MATRIZ 2 (multMatrix)\n";
    sendMSG(serverID, (void*)&m2->data, sizeof(int)*m2->rows*m2->cols);

    recvMSG(serverID, (void**)&resultado->data, &dataLen);

    if(dataLen != resultado->rows * resultado->cols) {
        std::cout << "LA MATRIZ PROBABLEMENTE ESTA MAL\n";
        // to fucking do
    }

    return resultado;
}


void multMatrixStub::writeMatrix(matrix_t* m, const char *fileName) {
    char msg = OP_WRITE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    sendMSG(serverID, (void*)&fileName, sizeof(fileName) + 1);

    int aux[2] = {m->rows, m->cols};
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    sendMSG(serverID, (void*)&m->data, sizeof(int)*m->rows*m->cols);
}

// precondicion: rows = cols
matrix_t* multMatrixStub::createIdentity(int rows, int cols) {
    int dataLen = 0;
    char msg = OP_CREATEIDENTITY;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int aux[2] = {rows, cols};
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    matrix_t *identity = nullptr;
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
    sendMSG(serverID, (void*)&aux, sizeof(int) * 2);

    matrix_t *randomMat = nullptr;
    randomMat->cols = cols;
    randomMat->rows = rows;
    
    recvMSG(serverID, (void**)&randomMat->data, &dataLen);

    return randomMat;
}  