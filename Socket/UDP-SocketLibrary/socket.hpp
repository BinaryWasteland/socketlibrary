#ifndef GUARD_socket_hpp20101209_
#define GUARD_socket_hpp20101209_

/** @file: socket.hpp
	@author Greg R. Jacobs
	@author greg.r.jacobs@gmail.com
	@author http://gregrjacobs.com
	@date 2010-12-09
	@version 0.0.0
	@note Developed for Visual C++ 10.0
	@brief ...
	*/


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

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>

enum TypeSocket {BlockingSocket, NonBlockingSocket};

class Socket {
public:

	virtual ~Socket();
	Socket(const Socket&);
	Socket& operator=(Socket&);
	std::string ReceiveLine();
	std::string ReceiveBytes();
	void   SendLine (std::string);
	void   SendBytes(const std::string&);
	void   Close();
protected:
	SOCKET s_;
	Socket();
	Socket(SOCKET s);
	int* refCounter_;
	friend class SocketServer;
	friend class SocketSelect;
private:
	static void Start();
	static void End();
	static int  numberOfSockets_;
};

#endif // GUARD_socket_hpp20101209_
