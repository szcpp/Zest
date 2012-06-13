#ifndef _CONTACTLIST_HPP_
#define _CONTACTLIST_HPP_
#include <ncurses.h>
#include <panel.h>
#include <form.h>
#include <menu.h>
#include <signal.h>
#include <cstring>
#include <vector>
#include <sstream>
#include "Contact.hpp"

/**
	@brief     ContactList class.
 	@details   Inheritance from class PANEL. While creating it checks statuses of all users, while a message about change of somebody's status is received it is refreshed.
 	@author    Anna Zaborowska
 	@version   0.1c
 	@date      09.06.2012
 	@copyright GNU Public License.
 */

class ContactList : public PANEL
{
	public:
		ContactList();
		void CreateList(std::vector<Contact*> choices);
		void GoUp();
		void GoDown();
		int GetContact();
	private:
		WINDOW* _win;
		ITEM **my_items;	
		MENU *my_menu;
};

#endif
