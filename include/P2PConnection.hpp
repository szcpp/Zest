#ifndef _P2PConnection_hpp_
#define _P2PConnection_hpp_
#include "Observable.hpp"
#include "Message.hpp"
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#define COMMUNICATION_PORT 7936
#define MAX_CONNECTIONS 100

/**
	@brief     Peer to peer connection class.
 	@details   P2P connection class. Represends single connection beetween users. When message comes it notifies all observers
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class P2PConnection : public Observable<Message>
{
public:
	/**
		A constructor.
		Maintains a connection beetween server and client.
		@param int socket handler.
		@param char[] IP address
		@exception P2PConnection::xConnectionFailure on connection error.
	*/
	P2PConnection(const int &socket, char ip[]);
	/**
		A constructor.
		Estabilishes a new connection to server.
		@param host server.
		@param port port.
		@exception P2PConnection::xConnectionFailure on connection error.
	*/
	P2PConnection(const char host[], const int port = COMMUNICATION_PORT);
	~P2PConnection(){};
	/**
		@param msg message to be sent.
		@return true on success.
	*/
	bool send(const Message &msg);
	/**
		Overloaded () operator.
		Used to notify all observers about received message.
	*/
	void operator()();
	/**
		Closes connection.
		@return true on success.
	*/
	bool closeSocket() { return (close(_socket) >= 0); };
private:
	/**
		IP address of remote host
	*/
	std::string _ipAddress;
	/**
		Signature used to start transmission
	*/
	const uint16_t _signature = 0x3efa;
	/**
		Connection handle.
	*/
	int _socket;
	/**
		Class used to throw object on connection failure.
	*/
	class xConnectionFailure{};
};

#endif