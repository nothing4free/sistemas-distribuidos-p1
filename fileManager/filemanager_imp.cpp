// SERVIDORn
// HOLA ESTOY EDITANDO DESDE VSCODE EN FIREFOX


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
    fm->freeListedFiles(vfiles);
}

void filemanager_imp::ListFiles() { // ls

    cout << " [LISTFILES]> Iniciando secuencia ListFiles...\n";
    int fileAmount = vfiles->size();

    // imprime archivos a listar
    for(unsigned int i=0;i<vfiles->size();++i)
    {
        cout<<" [LISTFILES]> Fichero detectado: "<<vfiles->at(i)->c_str()<<endl;
    }

    // imprime la cantidad de archivos a enviar
    std::cout << " [LISTFILES]> Ficheros a enviar: " << vfiles->size() << " \n";
    sendMSG(clientID, (void*)&fileAmount, sizeof(int)); // enviamos el tamano

    // debug del envio
    std::cout << " [LISTFILES]> Enviando ficheros: \n";
    for(int i = 0; i < vfiles->size(); i++) {
        std::cout << "              > " << vfiles->at(i)->c_str() << "\n";
        sendMSG(clientID, (void*)vfiles->at(i)->c_str(), sizeof(char) * vfiles->at(i)->length());
    }

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
    recvMSG(clientID, (void**)&fileName, &dataLen); //ok
    cout << " [READFILE]> Nombre de archivo recibido: " << fileName << "\n";

    // lee el archivo especificado
    cout << " [READFILE]> Leyendo archivo...\n";
    fm->readFile(fileName,data,fileLen);

    // envia el tamano del archivo
    cout << " [READFILE]> Enviando size del archivo: " << fileLen << "\n";
    sendMSG(clientID, &fileLen, sizeof(unsigned long int)); // envio del size

    // envia los contenidos del archivo
    cout << " [READFILE]> Enviando contenidos del archivo: \n\n" << data << "\n";
    sendMSG(clientID, (void*)data, sizeof(char*) * fileLen);
    cout << "\n\n";

}

void filemanager_imp::WriteFile() { // echo

    cout << " [WRITEFILE]> Iniciando secuencia WriteFile...\n";
    char* fileName = nullptr;
    char* fileContent = nullptr;
    string* fileContentStr = new string;
    int dataLen = 0;
    unsigned long int fileLen=0;

    // recibe el nombre del fichero
    recvMSG(clientID, (void**)&fileName, &dataLen);
    cout << " [WRITEFILE]> Recibido nombre de fichero: " << fileName << "\n";

    // recibe el contenido del fichero
    recvMSG(clientID, (void**)&fileContent, &dataLen);
    cout << " [WRITEFILE]> Recibido contenido: " << fileContent << "\n";
    fileContentStr->append(fileContent);
    fileLen = fileContentStr->length();

    // escribe en el fichero
    fm->writeFile(fileName, fileContent, fileLen);
    cout << " [WRITEFILE]> Fichero escrito correctamente.\n";

    delete fileContentStr;
}

void filemanager_imp::exec() { // bucle que escucha al cliente
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
                    salir = true;
                    char opOK = OP_OK;
                    sendMSG(clientID, (void*)&opOK, sizeof(char));
                    break;

            }
        }
    }
    cout << " [SERVER]> Cerrando conexion...\n";
}