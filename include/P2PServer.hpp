#ifndef _P2PServer_hpp_
#define _P2PServer_hpp_

/**
	@brief     Server class.
 	@details   Responsible of receiving new connections from contacts.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class P2PServer
{
public:
	/**
		A constructor.
		@param port port on which server will be listening.
		@exception P2PServer::xCouldNotStart error during start of server.
	*/
	P2PServer(const unsigned int port);
	~P2PServer();
	/**
		Restarts the server
		@return true on success.
	*/
	bool restart();
	/**
		Sets server port.
		@param port port.
	*/
	void setPort(const unsigned int port);
private:
	/**
		A socket handler.
	*/
	int _sock;
	/**
		Class used to throw an object, when problem with starting server appears.
	*/
	class xCouldNotStart{};
};

#endif