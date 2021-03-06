#include "Contact.hpp"
#include "Interface.hpp"

Contact::Contact(const std::string &name, const std::string &ip, const bool createConnection) : 
_ip(ip), _connection(0), _name(name), _status(OFFLINE), _thread(0)
{
	std::cerr << "laduje " << name << " ip:" << ip << std::endl;
	if(createConnection && ip.size() > 0)
	{// we are listening
		try
		{
			_connection = new P2PConnection(ip.c_str());
		}
		catch(P2PConnection::xConnectionFailure)
		{
			std::cerr << "FAILURE!" << std::cerr;
			_connection = 0;
			return;
		}
		_startListening();
	}
	else
		std::cerr << "CHUJOWEIP" << ip << std::endl;
}

Contact::~Contact()
{
	if(_thread != 0)
	{
		pthread_kill(_thread->native_handle(), SIGKILL);
		// delete _thread;
		// _thread = 0;
	}
	delete _connection;
}

void Contact::update(Message* message)
{
	// Interface::interface();
	if(message->type == Message::STATUS_CHANGE_OFFLINE)
	{
		_status = OFFLINE;
		delete removeConnection();
		Interface::interface().contactListUpdate();
		Interface::interface().ChatClose(_ip);
	}
	if(message->type == Message::STATUS_CHANGE_AVAILABLE)
	{
		_status = AVAILABLE;
		Interface::interface().contactListUpdate();
	}
	if(message->type == Message::MESSAGE)
	{
		Interface::interface().Write(message, Interface::interface().NewMessageReceived(_ip));
		msgLs.messages.push_back(*message);
	}
}

void Contact::setConnection(P2PConnection* connection)
{
	_connection = connection;
	_startListening();
}

P2PConnection* Contact::removeConnection()
{
	P2PConnection* c = _connection;
	_connection = 0;
	return c;
}

bool Contact::sendMessage(const Message &message)
{
	if(_connection != 0)
		return _connection->send(message);
	else return false;
}

std::vector<Contact*> Contact::loadContacts(const char* filename)
{
	std::vector<Contact*> contacts;
	std::string alias, address;
	std::fstream file (filename, std::fstream::in);
	while(!file.eof())
	{
		file >> alias >> address;
		std::cerr << alias << "::" << address << std::endl;
		contacts.push_back(new Contact(alias,address));
	}
	file.close();
	return contacts;
}

void Contact::saveContacts(const char* filename,const std::vector<Contact*>& contacts)
{
	std::fstream file (filename, std::fstream::out);
	for(auto it = contacts.begin(); it != contacts.end() ; ++it)
		file << (*it)->getName() << "\t" << (*it)->getIp() << std::endl;
	file.close();
}

void Contact::_startListening()
{
	if(_connection->getIP().size() > 3)
	{
		std::cerr << "NASLUCHUJE2: " << _connection->getIP() << std::endl;
		_connection->addObserver(this);
		_thread = new boost::thread(*_connection);
	}
	else
	{
		std::cerr << "CHUJOWEIP2:" << _connection->getIP() << std::endl;
		delete _connection;
		_connection = 0;
	}
}
