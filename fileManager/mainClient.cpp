#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "filemanager_stub.h"
#include "utils.h"

void help() {
    cout << "            > ls: lista los ficheros.\n";
    cout << "            > cat: lee un fichero.\n";
    cout << "            > echo: escribe en un fichero.\n";
    cout << "            > download: descarga un fichero.\n";
    cout << "            > upload: sube un fichero.\n";
    cout << "            > exit: cierra el cliente.\n";
    cout << "            > help: muestra esta pantalla de ayuda.\n";
}

int main() {
    filemanager_stub* fileClient = new filemanager_stub();
    string opcion = new char;

    cout << " [CLIENTE]> Cliente iniciado. Elija una opcion.\n";
    help();
    while(1<2) {
        cin >> opcion;
        if(opcion == "ls") {
            fileClient->ListFiles();

        } else if (opcion == "cat") {
            fileClient->ReadFile();

        } else if (opcion == "echo") {
            fileClient->WriteFile();

        } else if (opcion == "download") {
            // TODO

        } else if (opcion == "upload") {
            // TODO

        } else if (opcion == "exit") {
            break;

        } else if (opcion == "help") {
            help();

        } else {
            cout << " [CLIENTE]> ERROR: opcion invalida. Usa help para ver las opciones disponibles.\n";
        }
    }
    // interrumpir conexion con el servidor
    delete fileClient;
    return 0;
}