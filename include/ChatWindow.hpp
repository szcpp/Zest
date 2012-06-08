#ifndef _CHATWINDOW_HPP_
#define _CHATWINDOW_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <iostream>
#include <cstring>

/**
	@brief     ChatWindow class.
 	@details   Inheritance from class PANEL. It is created while a new talk is being started and refreshed after any message has been received.
 	@author    Anna Zaborowska
 	@version   0.1c
 	@date      08.06.2012
 	@copyright GNU Public License.
 */

class ChatWindow : public PANEL
{
	public:
		ChatWindow();
		//refresh();
		void Write(int where, std::string when,int who, std::string what);
		WINDOW* _win;
	private:
		chtype colourSb;
		chtype colourMe;
};

#endif
