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

class Contact
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
	Contact(const std::string name);
	~Contact(){};
	/**
		Checks status of contact
		@return current status
	*/
	Status checkStatus() const { return _status; }
	/**
		A pointer to connection object.
		When contact is not connectet, it is set to null.
	*/
	P2PConnection * _connection;
private:
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
