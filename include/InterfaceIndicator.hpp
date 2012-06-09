#ifndef _INTERFACEINDICATOR_HPP_
#define _INTERFACEINDICATOR_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <string>
#include <vector>

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
		InterfaceIndicator();
		void ChangeTalk(std::vector<std::string> chats, int active);
	private:
		WINDOW* _win;
};

#endif
