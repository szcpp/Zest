#include "P2PConnection.hpp"

// server
P2PConnection::P2PConnection(const int &socket, char ip[]) : _ipAddress(ip), _socket(socket) {}

// client
P2PConnection::P2PConnection(const char host[], const int port)
{
	_ipAddress = host;
	int option = 1;

	sockaddr_in clientAddress;
	memset(&(clientAddress.sin_zero), 0, 8);
	clientAddress.sin_family = AF_INET ;
	clientAddress.sin_port = htons(port);
	clientAddress.sin_addr.s_addr = inet_addr(host);

	_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct timeval timeout;      
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt (_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	{
		std::cerr << "Error setting options " << errno << std::endl;
		throw xConnectionFailure();
	}

    if (setsockopt (_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	{
		std::cerr << "Error setting options " << errno << std::endl;
		throw xConnectionFailure();
	}

	if(_socket < 0)
	{
		std::cerr << "Error initializing socket " << errno << std::endl;
		throw xConnectionFailure();
	}
	
	if((setsockopt(_socket, SOL_SOCKET, (SO_REUSEADDR | SO_KEEPALIVE), (char*) &option, sizeof(int)) < 0 ))
	{
		std::cerr << "Error setting options " << errno << std::endl;
		throw xConnectionFailure();
	}

	if(connect(_socket, (struct sockaddr*)&clientAddress, sizeof(clientAddress)) < 0 )
	{
		if(errno != EINPROGRESS)
		{
			std::cerr <<  "Error connecting socket " << errno << std::endl;
			//throw xConnectionFailure();
		}
	}
	// int error = 0;
	// socklen_t len = sizeof (error);
	// int retval = getsockopt (_socket, SOL_SOCKET, SO_ERROR, &error, &len );
	// if(retval != 0)
	// 	throw xConnectionFailure();
}

void P2PConnection::operator()()
{
	std::cerr << "NASLUCHUJE " << _ipAddress << std::endl;
	char buffer[256];
	unsigned short int i = 0;
	uint8_t type;
	uint16_t length, receivedSignature;
	Message * msg = 0;
	// we are now listening, so, status = online
	msg = new Message;
	msg->type = Message::STATUS_CHANGE_AVAILABLE;
	msg->ipAddress = _ipAddress;
	notifyObservers(msg);
	// delete msg;
	msg = 0;
	while(true)
	{
		time_t now; 
	   	struct tm *tm;
		char date[9];
		now=time(NULL);
		tm=localtime(&now);
		date[0] = (tm->tm_hour / 10) + '0' ;
		date[1] = (tm->tm_hour) % 10 + '0';
		date[2] = ':';
		date[3] = (tm->tm_min / 10) + '0' ;
		date[4] = (tm->tm_min) % 10 + '0';
		date[5] = ':';
		date[6] = (tm->tm_sec / 10) + '0' ;
		date[7] = (tm->tm_sec) % 10 + '0';
		date[8] = '\0';
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
				break;
			msg->content += buffer;
		}
		if(read(_socket, buffer, length % 256) <= 0);
			//break;
		msg->content += buffer;
		msg->ipAddress = _ipAddress;
		msg->date = date;
		notifyObservers(msg);
		delete msg;
	}
	std::cerr << "OFFLINE" << std::endl;
	// so if we are here, the connection is closed and peer went offline
	msg = new Message;
	msg->type = Message::STATUS_CHANGE_OFFLINE;
	msg->ipAddress = _ipAddress;
	notifyObservers(msg);
	// delete msg;
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
