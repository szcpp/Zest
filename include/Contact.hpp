#ifndef _Contact_hpp_
#define _Contact_hpp_
#include "P2PConnection.hpp"
#include "MessagesList.hpp"
#include <string>
#include <fstream>
#include <boost/thread.hpp>
#include <signal.h>

/**
	@brief     Contact
 	@details   Represents single element on contact list.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
    @file	   Contact.php
 */

class Contact : public Observer<Message>
{
public:
	/**
	*	Type representing status
	*/
	enum Status
	{
		AVAILABLE = 0,	/**< value representing contact being online */
		OFFLINE = 1,	/**< value representing contact being offline */
	};
	/**
		A constructor
		@param name a name of contact.
		@param ip ip address of contact
		@param createConnection should we create connection?
	*/
	Contact(const std::string &name, const std::string &ip,const bool createConnection = true);
	~Contact();
	/**
		Gets name of the contact
		@return contact's name
	*/
	const std::string& getName() const { return _name; }
	/**
		Checks status of contact
		@return current status
	*/
	const Status& getStatus() const { return _status; }
	/**
		Returns ip sddress of Contact
		@return ip address
	*/
	const std::string& getIp() const {return _ip;}

	/**
		Sets connection handler
		@param connection P2PConnection object
	*/
	void setConnection(P2PConnection*);

	/**
		Removes connection handler
		@return connection handler to be removed
	*/
	P2PConnection* removeConnection();

	/**
		Sends message to contact
		@param Message message to send
		@return true on success
	*/
	bool sendMessage(const Message&);
	
	MessagesList msgLs;
/*
DONE interface nasluchuje p2pserver, gdy nowe polaczenie, sprawdza ip z lista kontaktow (w notify()), nastepnie przypisuje polaczenie
DONE do konkretnego kontaktu (zrobic metode od tego ; zrobic metode od usuwania polaczenia, przy nadejsciu Message::Status::STATUS_CHANGE_OFFLINE)
contact odswieza liste kontaktow za pomoca metody w interface
DONE po wlaczeniu aplikacji, w oddzielnym watku tworzone sa polaczenia z kontaktami, po zakonczeniu watku interfejs zostaje odswiezony
*****przy nadejsciu wiadomosci contact otwiera nowe okno rozmowy (ewentualnie sprawdza czy takowe nie istnieje)
contact przy nadejsciu Message::Status::STATUS_CHANGE_OFFLINE zamyka okno rozmowy
DONE lista kontaktow w pliku, sprawdzane po odpaleniu aplikacji
DONE po podlaczeniu nowego kontaktu, dodanie do listy
DONE zapis przy zamykaniu aplikacji
mozna otwierac okno rozmowy tylko z osobami dostepnymi


dorobic metode send() i metode dodaj wiadomosc + pobierz liste

*/
	/**
		Observer - updates interface
		@param message message
	*/
	void update(Message*);

	/**
		Loads contacts from file
		@param filename filename of contacts file
		@return vector containing pointer to contacts
	*/
	static std::vector<Contact*> loadContacts(const char*);
	/**
		Saves contacts to a file
		@param filename filename of file
		@param contacts vector of contacts
	*/
	static void saveContacts(const char*,const std::vector<Contact*>&);
	
private:
	/**
		An ip address of remote host.
	*/
	std::string _ip;
	/**
		A pointer to connection object.
		When contact is not connectet, it is set to null.
	*/
	P2PConnection *_connection;

	/**
		Name of contact, which is being displayed on screen.
	*/
	std::string _name;
	/**
		Current status.
	*/
	Status _status;
	/**
		A pointer to listening thread.
	*/
	boost::thread *_thread;

	/**
		Starts listening for messages
	*/
	void _startListening();
};

#endif
