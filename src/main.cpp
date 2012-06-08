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
	time_t now; 
   struct tm *tm;
	int x=0;	
	char str[50];
	char date[9];
	memset(&str[0], 0, sizeof(str));
	while((ch = getch()) != 27)
	{
		if(ch== KEY_UP) {Interface::interface().Scroll(-1);}
		else
		{
			if(ch== KEY_DOWN) {Interface::interface().Scroll(1);}
			else
			{
				if(ch==127) // TODO Delete key ;)
				//if(ch==KEY_BACKSPACE)
				{
					Interface::interface().DelInput(x);
					x--;
					memset(&str[x], 0, 1);
					refresh();
				}
				else
				{
					str[x]=ch;
					Interface::interface().WriteInput(x,ch);
					refresh();
					x++;
				}
			}
		}
		switch(ch)
		{
			case '\n':
				now=time(NULL);
    			tm=localtime(&now);
				date[0] = (tm->tm_hour / 10) + '0' ;
				date[1] = (tm->tm_hour) % 10 + '0';
				date[2] = ':';
				date[3] = (tm->tm_min / 10) + '0' ;
				date[4] = (tm->tm_min) % 10 + '0';
				date[5] = ':';
				date[6] = (tm->tm_sec / 10) + '0' ;
				date[7] = (tm->tm_sec) % 10 + '0';
				date[8] = '\0';

				Interface::interface().Write(date,1,str);
				memset(&str[0], 0, sizeof(str));
				x=0;
				Interface::interface().ClearInput();
				break;
		}
	}
	Interface::interface().deinit();
	return 0;
}
