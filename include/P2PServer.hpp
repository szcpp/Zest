#ifndef _P2PServer_hpp_
#define _P2PServer_hpp_
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <boost/thread.hpp>
#include <signal.h>
#include "P2PConnection.hpp"

/**
	@brief     Server class.
 	@details   Responsible of receiving new connections from contacts.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class P2PServer : public Observable<P2PConnection>
{
public:
	/**
		A constructor.
	*/
	P2PServer(const unsigned int port = COMMUNICATION_PORT);
	~P2PServer(){ delete _thread;};
	/**
		Starts the server.
		@param port port on which server will be listening.
		@exception P2PServer::xCouldNotStart error during start of server.
	*/
	bool start();
	/**
		Stops the server.
		@return true on success
	*/
	bool stop();
	/**
		Listens for new connections.
		Entry point for a thread.
	*/
	void operator()();
private:
	/**
		A pointer to server thread.
	*/
	boost::thread * _thread;
	/**
		A port number.
	*/
	int _portNumber;
	/**
		A socket handler.
	*/
	int _socket;
	/**
		All connections.
	*/
	std::vector<P2PConnection*> _connections;
	/**
		Creates socket, and binds to it
		@return true on success
	*/
	bool _createSocket();
	/**
		Class used to throw an object, when problem with starting server appears.
	*/
	class xCouldNotStart{};
};

#endif