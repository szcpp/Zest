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
 	@version   0.1d
 	@date      08.06.2012
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
		void Write(std::string when, int who, std::string what);
		void WriteInput(int x,char ch);
		void DelInput(int x);
		void ClearInput();
		int ChatScroll=0;
	private:
		static Interface *interface_;
		std::map<std::pair<std::string, int>,std::string> messages;
		void rewrite();
		//PANEL* top;
		Interface();
};

#endif
