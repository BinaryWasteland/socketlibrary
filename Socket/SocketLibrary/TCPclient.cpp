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

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons( 27015 );

	if( connect( hSocket, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
		cerr << "Failed to connect\n";
		goto close;
	}

	char sendbuf[32] = "Hello";
	int bytesSent = send( hSocket, sendbuf, strlen(sendbuf)+1, 0 );
	cout << "Sent " << bytesSent << " bytes\n";
	char recvbuf[32] = "";
	int bytesRecv = recv( hSocket, recvbuf, 32, 0 );
	cout << "Received " << bytesRecv << " bytes\n"
		"Msg: " << recvbuf << endl;

close:
	closesocket( hSocket );
cleanup:
	WSACleanup();
}