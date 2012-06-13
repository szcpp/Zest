#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_
#include "ContactList.hpp"
#include "ChatWindow.hpp"
#include "InputField.hpp"
#include "MessagesList.hpp"
#include "InterfaceIndicator.hpp"
#include "P2PConnection.hpp"
#include "Contact.hpp"
#include <map>
#include <vector>
#include <string>

/**
	@brief     Interface class.
 	@details   Singleton pattern implementation, ncurses library usage to create windows.
 	@author    Anna Zaborowska
 	@version   0.1f
 	@date      12.06.2012
 	@copyright GNU Public License.
 */

class Interface : public Observer<P2PConnection>
{
	public:
		/**
			Enables creation of only one object of class Interface
		*/
		static Interface &interface();
		/**
			Inintialization of ncurses - creation of all the panels
		*/
		void init();
		/**
			Deinitialization of ncurses
		*/
		void deinit();
		/**
			Scrolls chat window
			@param how the number of scrolled lines (positive for scrolling down and negative for up)
		*/
		void Scroll(int how);
		/**
			Highlightes the next contact on contact list
		*/
		void NextContact();
		/**
			Highlightes the previous contact on contact list
		*/
		void PrevContact();
		/**
			Updates contact list after every change
		*/	
		void contactListUpdate();
		/**
			Changes chat window for the next one
		*/	
		void ChangeChat();
		/**
			Initializes a new chat
		*/
		void NewChatInit();
		/**
			Initializes a new chat after receiving message from somebody
			@param ip IP address of a sender
			@return the number of chat window connected with the sender
		*/
		int NewMessageReceived(const std::string &ip);
		/**
			Closes chat window (deletes appropriate item in _chatsOpened)
		*/	
		void ChatClose(const std::string &ip);
		/**
			Writes to an appropriate MessageList, prints message into chat window and send message to the contact
			@param what content of a message
		*/
		void Write(std::string what);
		/**
			Prints the message into an appropriate chat window 
			@param msgRec received message (to print)
			@param chatNo the number of chat connected with the sender
		*/
		void Write(Message* msgRec, int chatNo);
		/**
			Writes onto InputField characters one after another	
			@param x a position of character to print
			@param ch a character to print
		*/
		void WriteInput(int x,char ch);
		/**
			Deletes character from a specific position
			@param x position of a character to delete increased by 1
		*/
		void DelInput(int x);
		/**
			Clears all the InputField
		*/
		void ClearInput();
	private:
		/**
			A private constructor for the sake of singleton pattern
		*/
		Interface();
		/**
			A destructor
		*/
		~Interface();
		/**
			Recreates all the panels after the change of size of a terminal
		*/
		void recreate();
		/**
			Rewrites panels after the change of size of a terminal
		*/
		void rewrite();
		/**
			Updates panel and shows them on screen
		*/
		void updatePanels();
		/**
			Signal hadler recreating panels after the change of a terminal's size
			@param sig received signal
		*/
		static void winchSignalHandler(int sig);
		/**
			Adds contact to contact list
			@param contact a contact to be added
		*/
		void AddContact(Contact* contact);
		/**
			Updates Interface after getting a new connection
			@param conn connection opened
		*/
		void update(P2PConnection* conn);
		/**
			A pointer to the only object of an Interface class
		*/
		static Interface *_interface;
		/**
			A pointer to the class ContactList inheriting from PANEL
		*/
		ContactList* _contactList;
		/**
			A pointer to the class ChatWindow inheriting from PANEL			
		*/
		ChatWindow* _chatWindow;
		/**
			A pointer to the class InputField inheriting from PANEL
		*/
		InputField* _inputField;
		/**
			A pointer to the class InterfaceIndicator inheriting from PANEL
		*/
		InterfaceIndicator* _interfaceIndicator;
		/**
			An array of contacts' names shown in contact list
		*/
		std::vector < Contact* > _contactItems;
		/**
			A vector of contacts' names with whom there are chats opened
		*/
		std::vector<Contact*> _chatsOpened;
		/**
			A number of active chat window
		*/
		int _ActiveChat=0;
		/**
			A number of opened chats
		*/
		int _ChatNo=0;
};

#endif
