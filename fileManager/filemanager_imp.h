#pragma once

// linka con el cliente, reproduce la clase base

#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include "filemanager.h"

class filemanager_imp{
    private:
        FileManager * fm = new FileManager("./dirprueba/");
        bool salir = false;
        int clientID = 0;
        vector<string*> *vfiles;
    public:
        filemanager_imp();
        ~filemanager_imp();
        void ListFiles();
        void ReadFile();
        void WriteFile();
        void exec();
};