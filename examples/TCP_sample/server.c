/* 
	NaiveSocketLibrary TCP test server
	Listens on 0.0.0.0:5150
	Echos everything sent from client.
*/

#include <stdio.h>
#include <string.h> /* for memset() */
#include <stdbool.h>
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
    NSLInit();
	SOCKET sListen = NSLCreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	SOCKADDR *conn = NSLCreate3TupleV4("0.0.0.0", 5150);
	  
	NSLBindV4(sListen, conn);
	listen(sListen, 5); 
	printf("Binded\n");

	while(true)
	{
		SOCKET sNewConnection;
		SOCKADDR_IN clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));
		int clientAddrLen = sizeof(clientAddr);
		sNewConnection = accept(sListen, (SOCKADDR *)&clientAddr, &clientAddrLen);
		printf("Connected from %s\n", inet_ntoa(clientAddr.sin_addr));
		char message[] = "Hello world!";
		send(sNewConnection, message, sizeof(message), 0);
		char msg_recv[1024] = {0};
		int recvSize = recv(sNewConnection, msg_recv, 1024, 0);
		printf("Received: %s\n", msg_recv);
		NSLCloseSocket(sNewConnection);
	}

   NSLCloseSocket(sListen);
   NSLEnd();
   return 0;
}