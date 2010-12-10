/** @file: ReadMe.txt
	@author Greg R. Jacobs
	@author greg.r.jacobs@gmail.com
	@author http://gregrjacobs.com
	@date 2010-12-09
	@version 0.0.0
	@note Developed for Visual C++ 10.0
	@brief ...
	*/


This Document is to explain the usage of this application as well as document and credit sources that were used.

Code was assisted with http://www.adp-gmbh.ch/win/misc/sockets.html 
and was also assisted by Garth Santor's TCP and UDP client/server demos.  
Both very similar in code and allowed for a good base to start from.

How to use the application:


In the Win32 folder start the server first and then start the client afterwards to demonstrate that the client connects to the server.
Afterwards, in the client you can type words and press enter to have the words sent accross to the server where they will be echoed.
This can go on as long as possible until the user types 'exit'. In which case the client would shut down and the server would prompt you to exit.

Due to complications the send and recieve functions do not work but the client does connect to the server and is shown server-side via text.

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
