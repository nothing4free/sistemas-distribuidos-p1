#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "multmatrix.h"
#include "multMatrixImp.h"

void threadClient(int clientID)
{
	multMatrixImp* matrixImp = new multMatrixImp(clientID);
	matrixImp->exec();
	delete matrixImp;
	
}

int main(int argc,char** argv){

	int idSocket=0;
	idSocket=initServer(3301);
	while(true)
	{
	
		if(checkNewConnections()){
		
			int clientID=getNewConnection();	
			std::thread* newThread=new std::thread(threadClient,clientID);
			newThread->detach();
		}
	}

	return 0;
}