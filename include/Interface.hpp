#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_
#include "ContactList.hpp"
#include "ChatWindow.hpp"
#include "InputField.hpp"
#include "InterfaceIndicator.hpp"
#include <map>

/**
	@brief     Interface class.
 	@details   Singleton pattern implementation, ncurses library usage to create windows.
 	@author    Anna Zaborowska
 	@version   0.1c
 	@date      07.06.2012
 	@copyright GNU Public License.
 */

class Interface
{
	public:
		static Interface &interface();
		void init();
		void deinit();
		void Scroll(int how);
		int recreate();
		void updatePanels();
		void browse();
		static void winchSignalHandler(int sig);
		ContactList* _contactList;
		ChatWindow* _chatWindow;
		InputField* _inputField;
		InterfaceIndicator* _interfaceIndicator;
		void Write(char* when, int who, char* what)	;
		int ChatScroll=0;
	private:
		static Interface *interface_;
		std::map<char*,char*> messages;
		void rewrite();
		//PANEL* top;
		Interface();
};

#endif
