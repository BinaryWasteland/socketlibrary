/** @file: SocketSelect.cpp
	@author Greg R. Jacobs
	@author greg.r.jacobs@gmail.com
	@author http://gregrjacobs.com
	@date 2010-12-09
	@version 0.0.0
	@note Developed for Visual C++ 10.0
	@brief ...
	*/

#include "tcp_SocketSelect.hpp"

SocketSelect::SocketSelect(Socket const * const s1, Socket const * const s2) {
	FD_ZERO(&fds_);
	FD_SET(const_cast<Socket*>(s1)->s_,&fds_);
	if(s2) {
		FD_SET(const_cast<Socket*>(s2)->s_,&fds_);
	}     

	TIMEVAL tval;
	tval.tv_sec  = 0;
	tval.tv_usec = 1;

	TIMEVAL *ptval;
	
	ptval = &tval;
	

	if (select (0, &fds_, (fd_set*) 0, (fd_set*) 0, ptval) == SOCKET_ERROR) 
		throw "Error in select";
}

bool SocketSelect::Readable(Socket const* const s) {
	if (FD_ISSET(s->s_,&fds_)) return true;
	return false;
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
