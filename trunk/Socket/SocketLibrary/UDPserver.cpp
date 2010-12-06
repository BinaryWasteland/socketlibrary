#include <iostream>
using namespace std;
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

unsigned short const PORT = 49152;

int main() {
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
	serverAddress.sin_addr.s_addr	= htonl( INADDR_ANY );

	bind( hSocket, reinterpret_cast<sockaddr*>( &serverAddress ),
		sizeof(sockaddr_in) );

	// echo 10 packets
	for( int i = 0; i < 10; ++i ) {
		sockaddr	clientAddress;
		socklen_t	cbClientAddress = sizeof(clientAddress);
		int const MAXLINE = 256;
		char	msg[MAXLINE];
		int n = recvfrom( hSocket, msg, MAXLINE, 0, &clientAddress,
			&cbClientAddress );

		msg[0] = toupper(msg[0]);
		msg[min(n,255)] = 0;
		cout << "Recv: " << msg << endl;
		sendto( hSocket, msg, n, 0, &clientAddress, cbClientAddress );
	}

	// terminate WSA
	closesocket( hSocket );
	WSACleanup();
}