#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_
#include "ContactList.hpp"
#include "ChatWindow.hpp"
#include "InputField.hpp"
#include "InterfaceIndicator.hpp"

/**
	@brief     Interface class.
 	@details   Singleton pattern implementation, ncurses library usage to create windows.
 	@author    Anna Zaborowska
 	@version   0.1b
 	@date      26.05.2012
 	@copyright GNU Public License.
 */

class Interface
{
	public:
		static Interface &interface();
		void init();
		void deinit();
		int recreate();
		static void winchSignalHandler(int sig);
		ContactList* _contactList;
		ChatWindow* _chatWindow;
		InputField* _inputField;
		InterfaceIndicator* _interfaceIndicator;
	private:
		static Interface *interface_;
		Interface();
};

#endif
