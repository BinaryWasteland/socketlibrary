#include <iostream>
using namespace std;
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if (iResult != NO_ERROR ) {
		cerr << "WSAStartup failed" << endl;
		return 1;
	}

	SOCKET hSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if( hSocket == INVALID_SOCKET ) {
		cerr << "Error at socket(): " << WSAGetLastError() << endl;
		goto cleanup;
	}

	// bind the socket
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons( 27015 );

	if( bind( hSocket, (SOCKADDR*)&service, sizeof(service) ) == SOCKET_ERROR ) {
		cerr << "Bind() failed\n";
		goto close;
	}

	if( listen( hSocket, 1 ) == SOCKET_ERROR ) {
		cerr << "Error listening on socket\n";
		goto close;
	}

	cout << "Waiting for connection\n";
	SOCKET hAccepted = SOCKET_ERROR;
	while( hAccepted == SOCKET_ERROR ) {
		hAccepted = accept( hSocket, NULL, NULL );
	}
	cout << "Client connected\n";

	int bytesSent;
	char sendbuf[32] = "Goodbye";
	char recvbuf[32] = "";

	int bytesRecv = recv( hAccepted, recvbuf, 32, 0 );
	cout << "Recv = " << bytesRecv << ": " << recvbuf << endl;
	bytesSent = send( hAccepted, sendbuf, strlen(sendbuf)+1, 0 );
	cout << "Sent " << bytesSent << " bytes";

	closesocket( hAccepted );
close:
	closesocket( hSocket );
cleanup:
	WSACleanup();
}