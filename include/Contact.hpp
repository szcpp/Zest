#ifndef _Contact_hpp_
#define _Contact_hpp_
#include "P2PConnection.hpp"
#include <string>

/**
	@brief     Contact
 	@details   Represents single element on contact list.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
    @file	   Contact.php
 */

class Contact : public Observer<P2PConnection>
{
public:
	/**
	*	Type representing status
	*/
	enum Status
	{
		AVAILIBLE = 0,	/**< value representing contact being online */
		OFFLINE = 1,	/**< value representing contact being offline */
	};
	/**
		A constructor
		@param name a name of contact.
	*/
	Contact(const std::string name, const std::string ip);
	~Contact(){};
	/**
		Checks status of contact
		@return current status
	*/
	Status checkStatus() const { return _status; }

	const std::string& getIp() const {return _ip;}
	
	MessagesList msgLs;
/*
interface nasluchuje p2pserver, gdy nowe polaczenie, sprawdza ip z lista kontaktow (w notify()), nastepnie przypisuje polaczenie
do konkretnego kontaktu (zrobic metode od tego ; zrobic metode od usuwania polaczenia, przy nadejsciu Message::Status::OFFLINE)
contact odswieza liste kontaktow za pomoca metody w interface
po wlaczeniu aplikacji, w oddzielnym watku tworzone sa polaczenia z kontaktami, po zakonczeniu watku interfejs zostaje odswierzony
*****przy nadejsciu wiadomosci contact otwiera nowe okno rozmowy (ewentualnie sprawdza czy takowe nie istnieje)
contact przy nadejsciu Message::Status::OFFLINE zamyka okno rozmowy
lista kontaktow w pliku, sprawdzane po odpaleniu aplikacji
po podlaczeniu nowego kontaktu, dodanie do listy
zapis przy zamykaniu aplikacji
mozna otwierac okno rozmowy tylko z osobami dostepnymi


dorobic metode send() i metode dodaj wiadomosc + pobierz liste

*/
	
private:
	std::string _ip
	/**
		A pointer to connection object.
		When contact is not connectet, it is set to null.
	*/
	P2PConnection * _connection;

	/**
		Name of contact, which is being displayed on screen.
	*/
	std::string _name;
	/**
		Current status.
	*/
	Status _status;
};

#endif
