#ifndef _P2PCommunication_hpp_
#define _P2PCommunication_hpp_
#include <vector>

#define COMMUNICATION_PORT 7935

/**
	@brief     P2PCommunication.
 	@details   Peer to peer communication class. Provides abstraction layer to encryption of messages and TCP communication.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class P2PCommunication : public Observable
{
public:
	P2PCommunication();
	~P2PCommunication();
	/**
		Starts server
		@param port a port, on which server will be listening.
		@return true on success, false on failure.
		@exception P2PServer::xCouldNotStart error during start of server
	*/
	bool startServer(const unsigned int port = COMMUNICATION_PORT);
	/**
		Connects to another peer
		@param contact a pointer to Contact object, which represents contact
		@param port a port, on which server is listening.
		@return true on success, false on failure.
	*/
	bool connect(Contact * contact, const unsigned int port = COMMUNICATION_PORT);
	/**
		Sends message.
		@param message message to be sent.
		@return true on success, false on failure.
	*/
	bool sendMessage(const Message * message);
private:
	/**
		A pointer to server object.
	*/
	P2PServer * _server;
	/**
		A vector of estabilished connections.
	*/
	std::vector<P2PConnection*> _connections;
};

#endif