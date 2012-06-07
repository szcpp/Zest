#include "P2PConnection.hpp"

P2PConnection::P2PConnection(const int &socket, char ip[]) :  _ipAddress(ip), _socket(socket){}

P2PConnection::P2PConnection(const char host[], const int port)
{
	int option = 1;

	sockaddr_in clientAddress;
	memset(&(clientAddress.sin_zero), 0, 8);
	clientAddress.sin_family = AF_INET ;
	clientAddress.sin_port = htons(port);
	clientAddress.sin_addr.s_addr = inet_addr(host);

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(_socket < 0)
	{
		std::cerr << "Error initializing socket " << errno << std::endl;
		throw new xConnectionFailure();
	}
	
	if((setsockopt(_socket, SOL_SOCKET, (SO_REUSEADDR | SO_KEEPALIVE), (char*) &option, sizeof(int)) < 0 ))
	{
		std::cerr << "Error setting options " << errno << std::endl;
		throw new xConnectionFailure();
	}

	if(connect(_socket, (struct sockaddr*)&clientAddress, sizeof(clientAddress)) < 0 )
	{
		if(errno != EINPROGRESS)
		{
			std::cerr <<  "Error connecting socket " << errno << std::endl;
			throw new xConnectionFailure();
		}
	}
}

void P2PConnection::operator()()
{
	char buffer[256];
	unsigned short int i = 0;
	uint8_t type;
	uint16_t length, receivedSignature;
	Message * msg = 0;
	while(true)
	{
		msg = new Message;
		memset(&buffer, 0, 256);
		// message signature
		if((i = read(_socket, &receivedSignature, 2)) <= 0)
			break;
		if(receivedSignature != _signature)
		 	continue;
		// message type
		if(read(_socket, &type, 1) <= 0)
			break;
		msg->type = (Message::Type) type;
		// message length
		if(read(_socket, &length, 2) <= 0)
			break;
		// message content
		for(i = 0; i < (int)(length/256); ++i)
		{
			if(read(_socket, buffer, 256) <= 0)
				return;
			msg->content += buffer;
		}
		if(read(_socket, buffer, length % 256) <= 0)
			break;
		msg->content += buffer;
		msg->ipAddress = _ipAddress;
		notifyObservers(msg);
		delete msg;
	}
}

bool P2PConnection::send(const Message &msg)
{
	uint8_t type = (uint8_t) msg.type;
	uint16_t length = (uint16_t) msg.content.size();

	if(write(_socket, &_signature, 2) < 0)
		return false;
	if(write(_socket, &type, 1) < 0)
		return false;
	if(write(_socket, &length, 2) < 0)
		return false;
	if(write(_socket, msg.content.c_str(), length) < 0)
		return false;
	return true;
}