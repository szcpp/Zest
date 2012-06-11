#ifndef _MESSAGESLIST_HPP_
#define _MESSAGESLIST_HPP_
#include <map>
#include <vector>
#include <string>

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
		MessagesList();
		std::vector < std::string > messages;
		std::vector < std::string > date;
		std::vector < int > user;
		int size=0;
		void Add(std::string what, std::string when, int who);
};

#endif
