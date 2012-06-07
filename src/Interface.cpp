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
	update_panels(); // Update the stacking order. 2nd panel will be on top
	doupdate();	//Show it on the screen
}
void Interface::deinit()
{
	endwin();
}

void Interface::winchSignalHandler(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	Interface::interface().recreate();
	signal(SIGWINCH, winchSignalHandler);
}
