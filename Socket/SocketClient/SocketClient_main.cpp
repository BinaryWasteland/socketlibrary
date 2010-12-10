#include <iostream>
using namespace std;

#include "tcp_socket.hpp"
#include "tcp_SocketClient.hpp"
#include "tcp_SocketSelect.hpp"
#pragma comment (lib, "tcp-socket-gd-mt-vc10.0.lib")


unsigned short const PORT = 2000;

int main() {
	cout << "Client:\n";
  try {
    SocketClient s("127.0.0.1", PORT);
	cout << s.ReceiveLine();
	string line = "";
	while(cin >> line) {
		if(line == "exit")
			break;
		else
			s.SendLine(line);
	}

  } 
  catch (const char* s) {
    cerr << s << endl;
  } 
  catch (std::string s) {
    cerr << s << endl;
  } 
  catch (...) {
    cerr << "unhandled exception\n";
  }

  return 0;
}
