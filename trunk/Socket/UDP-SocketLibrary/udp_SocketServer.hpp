#ifndef GUARD_socketserver_hpp20101209_
#define GUARD_socketserver_hpp20101209_

/** @file: SocketServer.hpp
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
#include "udp_socket.hpp"

class SocketServer : public Socket {
public:
	SocketServer(int port, int connections, TypeSocket type=BlockingSocket);

	Socket* Accept();
};

#endif // GUARD_socketserver_hpp20101209_
