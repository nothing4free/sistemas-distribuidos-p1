// SERVIDOR

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "multmatrix.h"

class multMatrixImp {
    private:
        multMatrix* adminMatrices = nullptr;
        bool exitFlag = false;
        int clientID = 0;

    public:
        multMatrixImp(int clientID);
        ~multMatrixImp();
        void exec();
};