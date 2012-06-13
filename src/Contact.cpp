#include "Contact.hpp"

Contact::Contact(const std::string &name, const std::string &ip) : _name(name), _ip(ip)
{
	try
	{
		_connection = new P2PConnection(ip.c_str());
	}
	catch(P2PConnection::xConnectionFailure &exception)
	{
		_connection = 0;
	}
}

