#ifndef _CHATWINDOW_HPP_
#define _CHATWINDOW_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>

/**
	@brief     ChatWindow class.
 	@details   Inheritance from class PANEL. It is created while a new talk is being started and refreshed after any message has been received.
 	@author    Anna Zaborowska
 	@version   0.1a
 	@date      26.05.2012
 	@copyright GNU Public License.
 */

class ChatWindow : public PANEL
{
	public:
		ChatWindow();
		//refresh();
	private:
		WINDOW* _win;
};

#endif
