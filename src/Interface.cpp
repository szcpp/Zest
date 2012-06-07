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
	_chatWindow->Write(messages.size(), when, who, what);
}
void Interface::rewrite()
{
	int i=1;
	for (std::map<char*, char*>::iterator it = messages.begin(); it != messages.end(); ++it,++i)
	{
		_chatWindow->Write(i, it->first,1,it->second);
	}
	refresh();
}
