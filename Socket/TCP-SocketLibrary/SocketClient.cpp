/** @file: SocketClient.cpp
	@author Greg R. Jacobs
	@author greg.r.jacobs@gmail.com
	@author http://gregrjacobs.com
	@date 2010-12-09
	@version 0.0.0
	@note Developed for Visual C++ 10.0
	@brief ...
	*/


#include "tcp_SocketClient.hpp"

SocketClient::SocketClient(const std::string& host, int port) : Socket() {
	std::string error;

	hostent *he;
	if ((he = gethostbyname(host.c_str())) == 0) {
	error = strerror(errno);
	throw error;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = *((in_addr *)he->h_addr);
	memset(&(addr.sin_zero), 0, 8); 

	if (::connect(s_, (sockaddr *) &addr, sizeof(sockaddr))) {
	error = strerror(WSAGetLastError());
	throw error;
	}
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
