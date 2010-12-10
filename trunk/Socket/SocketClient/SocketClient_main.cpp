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

	string line = "";
	while(cin >> line) {
		s.SendLine(line);
	}

    //s.SendLine("GET");
	/*
    s.SendLine("Host: www.google.com");
    s.SendLine("");*/

    while (1) {
      string l = s.ReceiveLine();
      if (l.empty()) break;
      cout << l;
      cout.flush();
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
