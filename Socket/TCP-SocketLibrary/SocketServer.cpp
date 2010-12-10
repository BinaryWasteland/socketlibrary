/** @file: SocketServer.cpp
	@author Greg R. Jacobs
	@author greg.r.jacobs@gmail.com
	@author http://gregrjacobs.com
	@date 2010-12-09
	@version 0.0.0
	@note Developed for Visual C++ 10.0
	@brief ...
	*/
#include "tcp_SocketServer.hpp"

SocketServer::SocketServer(int port, int connections, TypeSocket type) {
	sockaddr_in service;
	//memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET /*or PF_INET*/;  
	service.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(port);  
	
	s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_ == INVALID_SOCKET) {
		Close();
		throw "INVALID_SOCKET";
	}

	if(type==NonBlockingSocket) {
	u_long arg = 1;
	ioctlsocket(s_, FIONBIO, &arg);
	}

	/* bind the socket to the internet address */
	if (bind(s_, (sockaddr *)&service, sizeof(sockaddr_in)) == SOCKET_ERROR) {
	closesocket(s_);
	throw "INVALID_SOCKET";
	}
  
	listen(s_, connections);     
}

Socket* SocketServer::Accept() {
	SOCKET hAccepted = accept(s_, NULL, NULL);
	if (hAccepted == INVALID_SOCKET) {
	int rc = WSAGetLastError();
	if(rc==WSAEWOULDBLOCK) {
		return 0; // non-blocking call, no request pending
	}
	else {
		throw "Invalid Socket";
	}
	}

	Socket* returnVal = new Socket(hAccepted);
	return returnVal;
}

/*=============================================================

Revision History

Version 0.0.0: 2010-12-09
Alpha release.

=============================================================

Copyright Greg R. Jacobs

The copyright to the computer program(s) herein
is the property of Greg R. Jacobs of Canada.
The program(s) may be used and/or copied only with
the written permission of Greg R. Jacobs
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
