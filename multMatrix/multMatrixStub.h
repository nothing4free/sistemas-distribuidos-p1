#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER 3301

typedef struct matrix_t
{
    int rows;
    int cols;
    int* data;
}matrix_t;

class multMatrixStub {
    private:
        int serverID = 0;
    
    public:
        multMatrixStub();
        ~multMatrixStub();
        matrix_t* readMatrix(const char* fileName);
        matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
        void writeMatrix(matrix_t* m, const char *fileName);
        matrix_t *createIdentity(int rows, int cols);
        matrix_t *createRandMatrix(int rows, int cols);

};