#include "udp_Socket.hpp"
#include <iostream>

using namespace std;


	int Socket::numberOfSockets_= 0;

	void Socket::Start() {
		if (!numberOfSockets_) {
			WSADATA wsaData;
			int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != NO_ERROR ) {
				throw "WSAStartup failed\n";
			}
		}
		++numberOfSockets_;
	}

	void Socket::End() {
		WSACleanup();
	}

	Socket::Socket()
	{
		Start();
		// UDP: use SOCK_DGRAM instead of SOCK_STREAM
		s_ = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

		if (s_ == INVALID_SOCKET) {
			throw "INVALID_SOCKET";
		}

		refCounter_ = new int(1);
	}

	Socket::Socket(SOCKET s) : s_(s) {
		Start();
		refCounter_ = new int(1);
	};

	Socket::~Socket() {
		if (! --(*refCounter_)) {
			Close();
			delete refCounter_;
		}

		--numberOfSockets_;
		if (!numberOfSockets_) 
		{
			End();
		}
	}

	Socket::Socket(const Socket& o) {
		refCounter_=o.refCounter_;
		(*refCounter_)++;
		s_         =o.s_;

		numberOfSockets_++;
	}

	Socket& Socket::operator=(Socket& o) {
		(*o.refCounter_)++;

		refCounter_=o.refCounter_;
		s_         =o.s_;

		numberOfSockets_++;

		return *this;
	}

	void Socket::Close() {
		closesocket(s_);
	}

	std::string Socket::ReceiveBytes() {
		std::string returnVal;
		char recvBuff[1024];
 
		while (1) {
			u_long arg = 0;

			if (arg == 0) 
				break;

			if (arg > 1024) 
				arg = 1024;

			int bytesRecv = recv (s_, recvBuff, arg, 0);
			if (bytesRecv <= 0) 
				break;
			std::string t;
			t.assign (recvBuff, bytesRecv);
			returnVal += t;
		}
 
		return returnVal;
	}

	std::string Socket::ReceiveLine() {
		std::string returnVal;
		while (1) {
			char recvByte;

			switch(recv(s_, &recvByte, 1, 0)) 
			{
				case 0:
				return returnVal;
				case -1:
				return "";
			}

			returnVal += recvByte;
			if (recvByte == '\n')  
				return returnVal;
		}
	}

	void Socket::SendLine(std::string sentLine) {
		sentLine += '\n';
		send(s_,sentLine.c_str(),sentLine.length(),0);
	}

	void Socket::SendBytes(const std::string& sentLine) {
		send(s_,sentLine.c_str(),sentLine.length(),0);
	}






