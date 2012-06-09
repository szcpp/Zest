#include "Interface.hpp"
#include <unistd.h>

Interface* Interface::interface_=NULL;

Interface& Interface::interface()
{
	if(interface_==NULL) interface_=new Interface();
	return *interface_;
}

Interface::Interface()
{
	init();
	signal(SIGWINCH, winchSignalHandler);
}

int Interface::recreate()
{
	deinit();
	init();
	rewrite();
	RecreateChat();
	return 1;
}

void Interface::init()
{
	initscr();
	refresh();
	clear();
	_contactList = new ContactList();
	_chatWindow=new ChatWindow();
	AddContacts();
	_contactList->CreateList(choices);
	_interfaceIndicator = new InterfaceIndicator();	
	_inputField = new InputField();
	updatePanels();
}
void Interface::updatePanels()
{
	update_panels();
	doupdate();
}
void Interface::deinit()
{
	endwin();
}

void Interface::winchSignalHandler(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	Interface::interface().recreate();
	Interface::interface().rewrite();
	signal(SIGWINCH, winchSignalHandler);
}
void Interface::Write(std::string when, int who, std::string what)
{
	msg[ActiveChat].Add(what,when,who);
	if(msg[ActiveChat].messages.size()<=LINES-3) _chatWindow->Write(msg[ActiveChat].messages.size()-1, when, who, what);
	if(msg[ActiveChat].messages.size()>LINES-3)
	{
		ChatScroll[ActiveChat]=msg[ActiveChat].messages.size()-LINES+2;
		recreate();
	}
}
void Interface::rewrite()
{
	_chatWindow->ClearWin();
	for (int it = 0; it != msg[ActiveChat].size; ++it)
	{
		if(it<ChatScroll[ActiveChat]) ;
		if(it>=ChatScroll[ActiveChat]&&it<ChatScroll[ActiveChat]+LINES-2) _chatWindow->Write(it-ChatScroll[ActiveChat], msg[ActiveChat].date[it], msg[ActiveChat].user[it], msg[ActiveChat].messages[it]);
	}
	refresh();
}
void Interface::Scroll(int how)
{
	if(how<0) if(ChatScroll[ActiveChat]!=0) ChatScroll[ActiveChat]+=how;
	if(how>0) if(msg[ActiveChat].messages.size()-ChatScroll[ActiveChat]>LINES-2) ChatScroll[ActiveChat]+=how;
	recreate();
	updatePanels();
}
void Interface::WriteInput(int x,char ch)
{
	_inputField->Write(x,ch);
}
void Interface::ClearInput()
{
	_inputField->Clear();
}
void Interface::DelInput(int x)
{
	_inputField->Del(x);
}
void Interface::NextContact()
{
	_contactList->GoDown();
}
void Interface::PrevContact()
{
	_contactList->GoUp();
}
void Interface::NewChat()
{
	_chatWindow->ClearWin();
	updatePanels();
	ActiveChat=ChatNo;
	ChatNo++;
	chats.push_back(*(choices+_contactList->GetContact()));
	_interfaceIndicator->ChangeTalk(chats, ActiveChat);	
}
void Interface::RecreateChat()
{
	_interfaceIndicator->ChangeTalk(chats, ActiveChat);
	updatePanels();
}
void Interface::ChangeChat()
{
	ActiveChat++;
	ActiveChat=ActiveChat%ChatNo;
	_interfaceIndicator->ChangeTalk(chats, ActiveChat);
	rewrite();
	doupdate();
}
void Interface::AddContacts()
{
	for(int i=0;i<10;i++)
		*(choices+i)="nowyU";
}
