#include <iostream>
#include "Message.hpp"
#include "P2PConnection.hpp"

class P2PTest : public Observer<P2PConnection>, public Observer<Message>
{
public:
	P2PTest(){};
	~P2PTest(){};
	// nasluchujemy nowych wiadomosci
	void update(Message* msg)
	{
		if(msg->type == Message::STATUS_CHANGE_OFFLINE)
			std::cout << "OFF" << std::endl;
		if(msg->type == Message::STATUS_CHANGE_AVAILABLE)
			std::cout << "ON" << std::endl;
		if(msg->type == Message::MESSAGE)
		{
			std::cout << "Message from " << msg->ipAddress << ": " << std::endl;
			std::cout << "---" << std::endl;
			std::cout << msg->content << std::endl;
			std::cout << "---" << std::endl;
		}
	}
	void update(P2PConnection* conn)
	{
		std::cout << "New connection from" << conn->getIP() << std::endl;
		// nowe polaczenie, podlaczamy sie jako listener nowych wiadomosci!
		conn->addObserver(this);
	}
};