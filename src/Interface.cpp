#include "Interface.hpp"
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
	//ChatScroll=0;
}

int Interface::recreate()
{
	deinit();
	init();
	rewrite();
	return 1;
}

void Interface::init()
{
	initscr();
	refresh();
	clear();
	_contactList = new ContactList();	
	_chatWindow = new ChatWindow();	
	_interfaceIndicator = new InterfaceIndicator();	
	_inputField = new InputField();
/*	set_panel_userptr(_contactList, _inputField);
	set_panel_userptr(_inputField, _chatWindow);
	set_panel_userptr(_chatWindow, _interfaceIndicator);
	set_panel_userptr(_interfaceIndicator, _contactList);
	top=_inputField;
	*/
	updatePanels();
}
void Interface::updatePanels()
{
	update_panels();
	doupdate();
}
/*
void Interface::browse()
{
	top = (PANEL *)panel_userptr(top);
	top_panel(top);	
	updatePanels();	

}
*/
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

void Interface::Write(char* when, int who, char* what)
{
	messages[when]=what;
	if(messages.size()<LINES-3)_chatWindow->Write(messages.size(), when, who, what);
	if(messages.size()>LINES-3)
	{
		ChatScroll++;
		recreate();
	}
}
void Interface::rewrite()
{
	int i=1;
	for (std::map<char*, char*>::iterator it = messages.begin(); it != messages.end(); ++it,++i)
	{
		if(i<=ChatScroll) ;
		if(i>ChatScroll&&i<ChatScroll+LINES-3) _chatWindow->Write(i-ChatScroll, it->first,1,it->second);
	}
	refresh();
}
void Interface::Scroll(int how)
{
	if(how<0) if(ChatScroll!=0) ChatScroll+=how;
	if(how>0) if(messages.size()-ChatScroll>LINES-2) ChatScroll+=how;
	recreate();
	updatePanels();
}
