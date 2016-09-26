#include <stdio.h>
#include <string.h> /* for memset() */
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
    NSLInit();
	SOCKET sListen = NSLCreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	int port = 5150;
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);    
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	  
	bind(sListen, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	
	listen(sListen, 5); 

	printf("Binded\n");

	while(true)
	{

		SOCKET	sNewConnection;
		SOCKADDR_IN clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));
		int clientAddrLen = sizeof(clientAddr);
		sNewConnection = accept(sListen, (SOCKADDR *)&clientAddr, &clientAddrLen);

		printf("Connected from %s\n", inet_ntoa(clientAddr.sin_addr));

		char message[] = "Welcome to Network Programing!";
		send(sNewConnection, message, sizeof(message), 0); 
		NSLCloseSocket(sNewConnection);
	}

   NSLCloseSocket(sListen);

   NSLEnd();
   return 0;
}