#include "Interface.hpp"
#include "P2PServer.hpp"
#include "Contact.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[])
{
	std::vector<Contact*> contacts = Contact::loadContacts("contact.list");

	P2PServer* server = new P2PServer;
	Interface& ui = Interface::interface();
	server->addObserver(&ui);
	server->start();

	for(auto it = contacts.begin(); it != contacts.end() ; ++it)
		ui.AddContact(*it);

	ui.init();
	keypad(stdscr, TRUE);
	int ch;	
	cbreak();
	noecho();
	int x=0;	
	char str[50];
	memset(&str[0], 0, sizeof(str));
	while((ch = getch()) != 27)
	{
		switch(ch)
		{
			case '\n':
				ui.Write(str);
				memset(&str[0], 0, sizeof(str));
				x=0;
				ui.ClearInput();
				break;
			case KEY_UP:
				ui.Scroll(-1);
				break;
			case KEY_DOWN:
				ui.Scroll(1);
				break;
			case KEY_RIGHT:
				ui.NextContact();
				break;
			case KEY_LEFT:
				ui.PrevContact();
				break;
			case 127:
				ui.DelInput(x);
				x--;
				memset(&str[x], 0, 1);
				refresh();
				break;
			case 43: // +
				ui.NewChatInit();
				refresh();
				break;
			case '\t': //tab
				ui.ChangeChat();
				refresh();
				break;
			default:
				if((int)ch> 32 && (int) ch<126)
				{
				    str[x]=ch;
				    Interface::interface().WriteInput(x,ch);
				    refresh();
				    x++;
				}
				break;
		}
	}
	ui.deinit();
	return 0;
}
