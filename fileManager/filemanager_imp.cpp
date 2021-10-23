// SERVIDORn

#include "filemanager_imp.h"
#include "filemanager.h"
#include "utils.h"

#define OP_READ   'R'
#define OP_WRITE  'W'
#define OP_LIST   'L'

#define OP_EXIT   'E'
#define OP_OK     'O'

// aqui se desarrollan los metodos de filemanager_imp.h.
// mirar los archivos operaciones_imp.h y operaciones_imp.cpp

filemanager_imp::filemanager_imp() {
    //fm = new FileManager("./dirprueba/");
    vfiles=fm->listFiles();
}

filemanager_imp::~filemanager_imp() {
    cout<<"Liberando lista de ficheros:\n";
    //fm->freeListedFiles(vfiles);
    cout<<"Liberando datos de fichero leído:\n";
}

void filemanager_imp::ListFiles() {

    cout << " [LISTFILES]> Iniciando secuencia ListFiles...\n";
    int fileAmount = vfiles->size();
    for(unsigned int i=0;i<vfiles->size();++i)
    {
        cout<<" [LISTFILES]> Fichero detectado: "<<vfiles->at(i)->c_str()<<endl;
    }

    std::cout << " [LISTFILES]> Ficheros a enviar: " << vfiles->size() << " \n";
    sendMSG(clientID, (void*)&fileAmount, sizeof(int)); // enviamos el tamano

    std::cout << " [LISTFILES]> Enviando ficheros: \n";
    for(int i = 0; i < vfiles->size(); i++) {
        std::cout << "              > " << vfiles->at(i)->c_str() << "\n";
        sendMSG(clientID, (void*)vfiles->at(i)->c_str(), sizeof(char) * vfiles->at(i)->length());
    }
    //fm->freeListedFiles(vfiles);

    std::cout << " [LISTFILES]> Ficheros enviados. \n";
}


void filemanager_imp::ReadFile() { // echo
    cout << " [READFILE]> Iniciando secuencia ReadFile, leyendo primer archivo del directorio...\n";
    char* data=nullptr;
    char* buff = nullptr;
    int dataLen = 0;
    unsigned long int fileLen=0;
    char *fileName = nullptr;
    string* fileNameStr = new string;

    // recibimos el nombre de archivo
    //cout << "RECVMSG INCOMING\n";
    recvMSG(clientID, (void**)&fileName, &dataLen); //ok
    cout << " [READFILE]> Nombre de archivo recibido: " << fileName << "\n";

    cout << " [READFILE]> Leyendo archivo...\n";
    fm->readFile(fileName,data,fileLen);

    cout << " [READFILE]> Enviando size del archivo: " << fileLen << "\n";
    sendMSG(clientID, &fileLen, sizeof(unsigned long int)); // envio del size

    cout << " [READFILE]> Enviando contenidos del archivo: \n\n" << data << "\n";
    sendMSG(clientID, (void*)data, sizeof(char*) * fileLen);
    cout << "\n\n";

}

void filemanager_imp::WriteFile() {
    cout << " [WRITEFILE]> Iniciando secuencia WriteFile...\n";
    char* fileName = nullptr;
    char* fileContent = nullptr;
    string* fileContentStr = new string;
    int dataLen = 0;
    unsigned long int fileLen=0;

    recvMSG(clientID, (void**)&fileName, &dataLen);
    cout << " [WRITEFILE]> Recibido nombre de fichero: " << fileName << "\n";

    recvMSG(clientID, (void**)&fileContent, &dataLen);
    cout << " [WRITEFILE]> Recibido contenido: " << fileContent << "\n";
    fileContentStr->append(fileContent);
    fileLen = fileContentStr->length();

    //cout<<"Escribiendo el primer fichero del directorio de prueba:\n";
    //fm->writeFile(&(*(vfiles->at(0)))[0],data,fileLen);
    fm->writeFile(fileName, fileContent, fileLen);
    cout << " [WRITEFILE]> Fichero escrito correctamente.\n";

    delete fileContentStr;
}

void filemanager_imp::exec() {
    while(salir!=true) { 
        char *msg = NULL;
        int dataLen = 0;
        char tipo_op = -1;

        recvMSG(clientID, (void**)&msg, &dataLen);

        if(dataLen == -1) { // maneja errores
            std::cout << "ERROR EN SERVIDOR: no hay datos.\n";
            std::cout << " |--------------> Fichero: " <<__FILE__ << "\n";
            std::cout << " |--------------> Linea: " << __LINE__ << "\n";
        } else {
            tipo_op = msg[0];
            delete msg;

            switch(tipo_op) {
                case OP_READ:
                    this->ReadFile();
                    break;
                case OP_WRITE:
                    this->WriteFile();
                    break;
                case OP_LIST:
                    this->ListFiles();
                    break;
                case OP_EXIT:
                    this->salir == true;
            }
        }
    }
}
