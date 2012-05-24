#ifndef _Message_hpp_
#define _Message_hpp_
#include "Contact.hpp"
#include <string>


/**
	@brief     Message class.
 	@details   Represents message exchanged beetween peers. Also notifies about presence of contact.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class Message
{
	/**
		Type of message
	*/
	enum Type
	{
		STATUS_CHANGE_AVAILIBLE = 0,	/**< Availibility notification. */
		STATUS_CHANGE_OFFLINE = 1,		/**< Unavailibility notification. */
		MESSAGE = 2 					/**< Regular message. */
	};
public:
	/**
		A constructor.
		@param _contact pointer to a contact, which i sender or receipient.
		@param type type of message.
		@param content content of message. If type is set to STATUS_CHANGE_AVAILIBLE or STATUS_CHANGE_OFFLINE, contents of this field is ignored.
	*/
	Message(const Contact *_contact, const Type type, const std::string content);
private:
	/**
		A pointer to a element in contact list.
	*/
	Contact *_contact;
	/**
		Type of message.
	*/
	Type _type;
	/**
		Content of message.
	*/
	std::string _content;
};
#endif