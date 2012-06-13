#ifndef _MESSAGESLIST_HPP_
#define _MESSAGESLIST_HPP_
#include <map>
#include <vector>
#include <string>
#include "Message.hpp"

/**
	@brief     MessagesList class.
 	@details   Created while new talk is started, it stores messages.
 	@author    Anna Zaborowska
 	@version   0.1a
 	@date      09.06.2012
 	@copyright GNU Public License.
 */

class MessagesList
{
	public:
		/**
			A constructor
		*/
		MessagesList();
		/**
			Adds new objects into vectors
			@param what object of class Message containing content of a message
			@param when date of sending/receiving message
			@param who number representing color of font for message
		*/
		void Add(Message what, std::string when, int who);
		/**
			Vector of messages
		*/
		std::vector < Message > messages;
		/**
			A scroll position for chat window
		*/
		int _ChatScroll;
};

#endif
