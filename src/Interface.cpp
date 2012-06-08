#include "Interface.hpp"
#include<unistd.h>

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
	// sleep(100);
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
	//Interface::interface()._inputField->_win.rewrite();
	signal(SIGWINCH, winchSignalHandler);
}
void Interface::Write(std::string when, int who, std::string what)
{
	messages[make_pair(when,who)]= what;
	if(messages.size()<=LINES-3)_chatWindow->Write(messages.size()-1, when, who, what);
	if(messages.size()>LINES-3)
	{
		ChatScroll=messages.size()-LINES+2;
		recreate();
	}
}
void Interface::rewrite()
{
	int i=0;
	for (std::map<std::pair<std::string, int>,std::string>::iterator it = messages.begin(); it != messages.end(); ++it,++i)
	{
		if(i<ChatScroll) ;
		if(i>=ChatScroll&&i<ChatScroll+LINES-2) _chatWindow->Write(i-ChatScroll, it->first.first,it->first.second,it->second);
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
