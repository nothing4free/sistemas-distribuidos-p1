// CLIENTE

#include "filemanager_stub.h"
#include "utils.h"

#define READ  'R'
#define WRITE 'W'
#define LIST  'L'

#define OP_EXIT  'E'
#define OP_OK    'O'

#define PORT_SERVER 31000     // sustituir por puerto de k8s ()
#define IP_SERVER "127.0.0.1" // sustituir por IP del nodo esclavo

// aqui se desarrollan los metodos de filemanager_stub.h.
// mirar los archivos operaciones_imp.h y operaciones_imp.cpp

filemanager_stub::filemanager_stub() {

    vfiles = fm->listFiles(); // pasar listFiles(directorio sshfs)
    char* ip = NULL;
    ip=new char[strlen(IP_SERVER)+1];
	memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

	std::cout<<" [CLIENTE]> Iniciando cliente...\n";

	serverID=initClient(ip,PORT_SERVER);
	if(serverID==-1)
	{
		std::cout<<"ERROR CLIENTE Fichero: "<<__FILE__<<" Línea: "<<__LINE__<<" Conexion no válida\n";
	}
	
	delete ip;
}

filemanager_stub::~filemanager_stub() {
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

void filemanager_stub::ListFiles() {

    cout << " [LISTFILES]> Iniciando secuencia ListFiles...\n";
    char msg = LIST;
    char* buff = nullptr;
    int fileAmt = 0;
    int dataLen = 0;

    vector<string*>* fileList = new vector<string*>();
   
   // enviar orden "LIST"
    sendMSG(serverID, (void*)&msg, sizeof(char)); 

    // recibimos la cantidad de archivos para determinar cuantas veces
    // se repetira el bucle q repite dichos nombres de archivo
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&fileAmt, buff, sizeof(int));
    delete buff;

    cout << " [LISTFILES]> Ficheros a recibir: " << fileAmt << "\n";

    // muestra ficheros a recibir
    for(int i = 0; i < fileAmt; i++) {
        recvMSG(serverID, (void**)&buff, &dataLen);
        string *tempFileName = new string;
        tempFileName->append(buff);
        fileList->push_back(tempFileName);
        cout << "               > " << fileList->at(i)->c_str() << "\n";
        delete tempFileName;
        delete buff;
    }

    cout << " [LISTFILES]> Ficheros recibidos.\n\n";
}

void filemanager_stub::ReadFile() {
    
    char msg = READ;
    char* buff = nullptr;
    int dataLen = 0;
    int fileSize = 0;
    char* fileNameChar = new char;
    string* fileContent = new string;
    
    cout << " [READFILE]> Iniciando secuencia ReadFile...\n";
    sendMSG(serverID, (void*)&msg, sizeof(char)); // va al exec()
 
    // enviar el nombre
    cout << " [READFILE]> Introduzca el nombre del fichero a leer...\n";
    cin >> fileNameChar;
    sendMSG(serverID, (void*)fileNameChar, (strlen(fileNameChar) + 1));

    // recibir el size
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&fileSize, buff, sizeof(int));
    cout << " [READFILE]> Tamano del archivo recibido: " << fileSize << "\n";
    delete buff;

    // recibir contenidos
    recvMSG(serverID, (void**)&buff, &dataLen);
    fileContent->append(buff);
    cout << " [READFILE]> Mostrando contenido del archivo recibido: ------------------------ \n\n" << fileContent->c_str() << "\n";
    delete buff;
    cout << "\n";
    cout << " [READFILE]> Archivo recibido. ------------------------------------------------\n\n";
}

void filemanager_stub::WriteFile() {

    char *fileName = new char;
    char *fileContent = new char;

    cout << " [WRITEFILE]> Iniciando secuencia WriteFile...\n";
    cout << " [WRITEFILE]> Introduzca el nombre del fichero a escribir...\n";
    cin >> fileName;
    cout << " \n[WRITEFILE]> Introduzca el contenido del fichero a escribir...\n";
    cin >> fileContent;

    char msg = WRITE;
    int dataLen = 0;

    // envio de orden "WRITE"
    sendMSG(serverID, (void*)&msg, sizeof(char));
    
    cout << " [WRITEFILE]> Escribiendo archivo " << fileName << "\n";
    // envio de nombre de archivo
    sendMSG(serverID, (void*)fileName, strlen(fileName) + 1);

    cout << " [WRITEFILE]> Enviando contenidos del archivo...\n";
    // envio del contenido
    sendMSG(serverID, (void*)fileContent, strlen(fileContent) + 1);
    cout << " [WRITEFILE]> Archivo enviado correctamente.\n";
}

void filemanager_stub::download() {
    cout << " [DOWNLOAD]> Iniciando secuencia download...\n";
    cout << " [DOWNLOAD]> Introduzca el nombre del fichero a descargar...\n";
    
    char msg = LIST;
    char* buff = nullptr;
    int fileAmt = 0;
    int dataLen = 0;


    // LIST FILES ---------------------------------------------------------
    char *fileName = new char;

    vector<string*>* fileList = new vector<string*>();
   
    // enviar orden "LIST"
    sendMSG(serverID, (void*)&msg, sizeof(char)); 

    // recibimos la cantidad de archivos para determinar cuantas veces
    // se repetira el bucle q repite dichos nombres de archivo
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&fileAmt, buff, sizeof(int));
    delete buff;

    for(int i = 0; i < fileAmt; i++) {
        recvMSG(serverID, (void**)&buff, &dataLen);
        string *tempFileName = new string;
        tempFileName->append(buff);
        fileList->push_back(tempFileName);
        cout << "               > " << fileList->at(i)->c_str() << "\n";
        delete tempFileName;
        delete buff;
    }

    cin >> fileName;

    // READ FILES ---------------------------------------------------------

    msg = READ;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int fileSize = 0;
    char* fileNameChar = new char;
    char* fileContent = nullptr;

    // enviar el nombre
    sendMSG(serverID, (void*)fileName, (strlen(fileName) + 1));

    // recibir el size
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&fileSize, buff, sizeof(int));
    delete buff;

    // recibir contenidos
    recvMSG(serverID, (void**)&fileContent, &dataLen);
    fm->writeFile(fileName, fileContent, dataLen); // escribimos en directorio

    cout << " [DOWNLOAD]> Archivo descargado.\n";
}

void filemanager_stub::upload() {
    cout << " [UPLOAD]> Iniciando secuencia upload...\n";
    cout << " [UPLOAD]> Introduzca el nombre del fichero a subir...\n";
    vector<string*>* fileList = new vector<string*>();

    // realiza listado de archivos en local
    fileList = fm->listFiles();
    int localFileAmount = fileList->size();

    // muestra los ficheros en local
    for(int i = 0; i < localFileAmount; i++) {
        cout << " > " << fileList->at(i)->c_str() << "\n";
    }
    
    char *fileName = new char;
    char *fileContent = nullptr;
    unsigned long int fileLen = 0;

    cin >> fileName;

    // WRITE ------------------------------------------------------------

    // envio de la orden
    char msg = WRITE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    // envio del nombre
    sendMSG(serverID, (void*)fileName, strlen(fileName) + 1);

    fm->readFile(fileName, fileContent, fileLen);
    // envio del contenido
    sendMSG(serverID, (void*)fileContent, sizeof(fileContent) + 1);

    cout << " [UPLOAD]> Fichero subido correctamente.\n";

}