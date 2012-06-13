#include "Interface.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[])
{
	Interface::interface().init();
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
				Interface::interface().Write(str);
				memset(&str[0], 0, sizeof(str));
				x=0;
				Interface::interface().ClearInput();
				break;
			case KEY_UP:
				Interface::interface().Scroll(-1);
				break;
			case KEY_DOWN:
				Interface::interface().Scroll(1);
				break;
			case KEY_RIGHT:
				Interface::interface().NextContact();
				break;
			case KEY_LEFT:
				Interface::interface().PrevContact();
				break;
			case 127:
				Interface::interface().DelInput(x);
				x--;
				memset(&str[x], 0, 1);
				refresh();
				break;
			case 43: // +
				Interface::interface().NewChatInit();
				refresh();
				break;
			case '\t': //tab
				Interface::interface().ChangeChat();
				refresh();
				break;
			default:
				str[x]=ch;
				Interface::interface().WriteInput(x,ch);
				refresh();
				x++;
				break;
		}
	}
	Interface::interface().deinit();
	return 0;
}
