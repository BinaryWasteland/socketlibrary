#include <iostream>
#include <process.h>
using namespace std;

#include "tcp_socket.hpp"
#include "tcp_SocketServer.hpp"
#pragma comment (lib, "tcp-socket-gd-mt-vc10.0.lib")


unsigned short const PORT = 2000;
unsigned short const NUM_CONN = 5;

//unsigned __stdcall Answer(void* a) {
//  Socket* s = (Socket*) a;
//  while (1) {
//	std::string r = s->ReceiveLine();
//	if (r.empty()) 
//	{
//		break;
//	}
//	s->SendLine(r);
//  }
//  delete s;
//  return 0;
//}



int main(int argc, char* argv[]) {
	cout << "Server:\n";
	SocketServer sockServ(PORT, NUM_CONN);
	
	cout << "Waiting for connection...\n";
	Socket* s = sockServ.Accept();
	cout << "Client connected\n";
	
	while( true ) {
		cout << sockServ.ReceiveLine();
		//unsigned returnVal;
		//_beginthreadex(0,0,Answer,(void*) s,0,&returnVal);
		
	}
}