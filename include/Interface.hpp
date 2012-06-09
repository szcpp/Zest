#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_
#include "ContactList.hpp"
#include "ChatWindow.hpp"
#include "InputField.hpp"
#include "MessagesList.hpp"
#include "InterfaceIndicator.hpp"
#include <map>
#include <vector>
#include <string>

/**
	@brief     Interface class.
 	@details   Singleton pattern implementation, ncurses library usage to create windows.
 	@author    Anna Zaborowska
 	@version   0.1e
 	@date      09.06.2012
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
		void RecreateChat();
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
		void NextContact();
		void PrevContact();
		void NewChat();
		void ChangeChat();
		int ChatScroll[100];
		std::string choices[100];
		std::vector<std::string> chats;
		void AddContacts();
		int ActiveChat=0;
		int ChatNo=0;
	private:
		static Interface *interface_;
		MessagesList msg[100];
		void rewrite();
		PANEL* top;
		Interface();
};

#endif
