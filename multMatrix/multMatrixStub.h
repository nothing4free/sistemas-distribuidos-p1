#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 3301

class multMatrixStub {
    private:
        int serverID = 0;
    
    public:
        multMatrixStub();
        ~multMatrixStub();
};