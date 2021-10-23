#pragma once

#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include "filemanager.h"

class filemanager_stub{
    private:
        //FileManager * fm = new FileManager;
        bool salir = false;
        int serverID = 0;
    public:
        filemanager_stub();
        ~filemanager_stub();
        void ListFiles();
        void ReadFile();
        void WriteFile();
};