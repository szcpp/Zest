#include "P2PServer.hpp"

P2PServer::P2PServer(const unsigned int port) : _portNumber(port) {}

bool P2PServer::start()
{
	if(!_createSocket())
		return false;
	_listen();
	return true;
}

bool P2PServer::_createSocket()
{
	int option = 1;

	sockaddr_in serverAddress;
	memset(&(serverAddress.sin_zero), 0, 8);
	serverAddress.sin_family = AF_INET ;
	serverAddress.sin_port = htons(_portNumber);
	serverAddress.sin_addr.s_addr = INADDR_ANY ;

	// creating socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(_socket == -1)
	{
		std::cerr << "Error creating socket: " << errno << std::endl;
		return false;
	}

	if(setsockopt(_socket, SOL_SOCKET, (SO_REUSEADDR | SO_KEEPALIVE), (char*)&option, sizeof(option)) < 0)
	{
		std::cerr << "Error setting socket options: " << errno << std::endl;
		return false;
	}
	
	if( bind(_socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
		std::cerr << "Error binding to socket, make sure nothing else is listening on this port " << errno << std::endl;
		return false;
	}

	if(listen(_socket, MAX_CONNECTIONS) < 0)
	{
		std::cerr << "Error listening " << errno << std::endl;
		return false;
	}

	return true;;
}

void P2PServer::_listen()
{
	sockaddr_in sadr;
	socklen_t addr_size = sizeof(sockaddr_in);
	int socketHandle;
	P2PConnection *connection;
	boost::thread_group threads;
	
	while(true)
	{
		if((socketHandle = accept(_socket, (sockaddr*)&sadr, &addr_size))!= -1)
		{
			connection = new P2PConnection(socketHandle,inet_ntoa(sadr.sin_addr));
			_connections.push_back(connection);
			notifyObservers(connection);
			threads.create_thread(boost::ref(*connection));
		}
		else
			std::cerr << "Error accepting connection " << errno << std::endl;
	}
	for (auto it = _connections.begin(); it != _connections.end(); ++it)
		delete *it;
}