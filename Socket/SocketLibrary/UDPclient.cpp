#include <iostream>
#include <string>
using namespace std;

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

unsigned short const PORT = 49152;

int main( int argc, char* argv[] ) {

	// initialize WSA
	WSAData wsaData;
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if( iResult != 0 ) {
		cerr << "WSAStartup failed: " << iResult << endl;
		return 1;
	}

	// create the UDP socket
	SOCKET hSocket = socket( AF_INET, SOCK_DGRAM, 0 );

	// create the server address
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family		= AF_INET;
	serverAddress.sin_port			= htons( PORT );
	serverAddress.sin_addr.s_addr	= inet_addr( argv[1] );

	// Send lines to be echoed.
	int const MAXLINE = 256;
	char recvLine[ MAXLINE + 1 ];

	string line;
	while( getline( cin, line ) ) {
		sendto( hSocket, line.c_str(), line.size(), 0, 
			reinterpret_cast<sockaddr*>( &serverAddress ),
			sizeof(serverAddress) );

		int n = recvfrom( hSocket, recvLine, MAXLINE, 0, NULL, NULL );
		recvLine[n] = 0;
		cout << recvLine << endl;
	}


	// terminate WSA
	closesocket( hSocket );
	WSACleanup();
}