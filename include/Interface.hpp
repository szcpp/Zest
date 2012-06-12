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

class Interface : public Observer<P2PConnection>, public Observer<Message>
{
	public:
		/**
			Enables creation of only one object of class Interface
		*/
		static Interface &interface();
		/**
			Inintialization of ncurses - creation of all panels
		*/
		void init();
		/**
			Deinitialization of ncurses
		*/
		void deinit();
		/**
			Scrolls chat window
			@param how a number of scrolled lines (positive for scrolling down and negative for up)
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
			Changes chat window for the next one
		*/
		void ChangeChat();
		/**
			Initializes a new chat
		*/
		void NewChatInit();
		/**
			Initializes a new chat after receiving message from somebody
			@param msgRec received message
		*/
		void NewChatReceive(Message* msgRec);
		/**
			Writes to an appropriate MessageList, prints message into chat window and send message to the contact
			@param when date of sending/receiving message, format hh:mm:ss
			@param who a number representing color of font for message
			@param what content of a message
		*/
		void Write(std::string when, int who, std::string what);
		/**
			Writes to an appropriate MessageList, prints message into chat window 
			@param msgRec received message
		*/
		void Print(Message* msgRec);
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
			Adds contacts to contact list
		*/
		void AddContacts();
		/**
			Updates Interface after Message received
			@param msgRec received message
		*/
		void update(Message* msgRec);
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
			An array of objects of class MessagesList
		*/
		MessagesList _msg[20];
		/**
			A scroll position for every chat window opened
		*/
		int _ChatScroll[20];
		/**
			An array of contacts' names shown in contact list
		*/
		std::string _contactItems[100];
		/**
			A vector of contacts' names with whom there are chats opened
		*/
		std::vector<std::string> _chatsOpened;
		/**
			A vector of objects of class Contact
		*/
		std::vector<Contact> _contactsConnected; 
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
