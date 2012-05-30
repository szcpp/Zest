#ifndef _P2PConnection_hpp_
#define _P2PConnection_hpp_
#include "Observable.hpp"
#include "Message.hpp"

#define COMMUNICATION_PORT 7935

/**
	@brief     Peer to peer connection class.
 	@details   P2P connection class. Represends single connection beetween users.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class P2PConnection : public Observable
{
public:
	/**
		A constructor.
		Estabilishes a new connection to server.
		@param host server.
		@param port port.
		@exception P2PConnection::xConnectionFailure on connection error.
	*/
	P2PConnection(const int host, const int port);
	~P2PConnection();
	/**
		@param msg message to be sent.
		@return true on success.
	*/
	// bool send(const Message msg);
	/**
		Reads message from socket.
		@return Message.
	*/
	//Message receive();
private:
	/**
		Connection handle.
	*/
	int _connection;
	/**
		Class used to throw object on connection failure.
	*/
	class xConnectionFailure{};
};

#endif