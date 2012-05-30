#ifndef _CONTACTLIST_HPP_
#define _CONTACTLIST_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>

/**
	@brief     ContactList class.
 	@details   Inheritance from class PANEL. While creating it checks statuses of all users, while a message about change of somebody's status is received it is refreshed.
 	@author    Anna Zaborowska
 	@version   0.1a
 	@date      26.05.2012
 	@copyright GNU Public License.
 */

class ContactList : public PANEL
{
	public:
		ContactList();
		//refresh();
		//checkStatuses();
	private:
		WINDOW* _win;
};

#endif
