#ifndef _INTERFACEINDICATOR_HPP_
#define _INTERFACEINDICATOR_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <string>
#include <vector>
#include "Contact.hpp"

/**
	@brief     InputField class.
 	@details   Inheritance from class PANEL. It shows all chats and shows a navigation bar.
 	@author    Anna Zaborowska
 	@version   0.1b
 	@date      09.06.2012
 	@copyright GNU Public License.
 */

class InterfaceIndicator : public PANEL
{
	public:
		/**
			A constructor
		*/
		InterfaceIndicator();
		/**
			Changes the chat window - prints once again all senders' names with active window being bold
			@param chats vector of contacts we are talking to
			@param active the number of an active chat
		*/
		void ChangeTalk(std::vector<Contact*> chats, int active);
		/**
			Clears window;
		*/
		void Clear();
	private:
		/**
			Window in which names are displayed
		*/
		WINDOW* _win;
};

#endif
