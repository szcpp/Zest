#ifndef _Message_hpp_
#define _Message_hpp_
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
public:
	/**
		Type of message
	*/
	enum Type
	{
		STATUS_CHANGE_AVAILABLE = 0,	/**< Availibility notification. */
		STATUS_CHANGE_OFFLINE = 1,		/**< Unavailibility notification. */
		MESSAGE = 2 					/**< Regular message. */
	};
	/**
		IP Address of sender
	*/
	std::string ipAddress;
	/**
		Type of message.
	*/
	Type type;
	/**
		Content of message.
	*/
	std::string content;
	/**
		Date (format hh:mm:ss)
	*/
	std::string date;
};
#endif
