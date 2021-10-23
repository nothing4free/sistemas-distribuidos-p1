#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "filemanager_imp.h"
#include "utils.h"

void threadClient(int clientID) {
    filemanager_imp* fileServer = new filemanager_imp();
    fileServer->exec();
    delete fileServer;

}

int main() {

    cout << " [SERVER]> Iniciando servidor... \n";
    int idSocket = 0;
    idSocket = initServer(3301);

    while(true) {
        //cout << "PASANDO AL IF \n";
        if(checkNewConnections()) {
            int clientID = getNewConnection();
            std::thread* newThread = new std::thread(threadClient, clientID);
            newThread->detach();
        }
    }
    cout << "out of the loop\n";
    /*
    while(1 < 2) {
        if(checkNewConnections()) {
            int clientID = getNewConnection();
            std::thread* newThread = new std::thread(threadClient, clientID);
            newThread->detach();
        }
    }    
    */
   return 0;
}