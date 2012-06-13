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
		/**
			A constructor
		*/
		ContactList();
		/**
			Creates contact list, checks statuses of contacts
			@param contacts a vector of pointer to Contacts 
		*/
		void CreateList(std::vector<Contact*> contacts);
		/**
			Moves to the previous item in menu
		*/
		void GoUp();
		/**
			Moves to the next item in menu
		*/
		void GoDown();
		/**
			Gets number of contact being selected
		*/
		int GetContactNo();
	private:
		/**
			Window in which menu is displayed
		*/
		WINDOW* _win;
		/**
			Items in menu
		*/
		ITEM **my_items;
		/**
			Menu collecting items
		*/
		MENU *my_menu;
};

#endif
