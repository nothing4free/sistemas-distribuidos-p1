// CLIENTE

#include "multMatrixStub.h"
#include <string.h>

#define OP_OK             'O'
#define OP_EXIT           'E'

#define OP_READ           'R'
#define OP_MULT           'M'
#define OP_WRITE          'W'
#define OP_CREATEIDENTITY 'I'
#define OP_CREATERANDOM   'A' // "A" de aleatorio, era mas logico usar R para read.

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