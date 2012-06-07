#include "Interface.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Interface::interface().init();
	int ch;	
	noecho();
	time_t now; 
   struct tm *tm;
	int x=0;	
	char str[50];
	char* date;
	std::stringstream sstm;
	std::string s;
	while((ch = getch()) != 27)
	{
		mvaddch(LINES-1,x,ch);
		str[x]=ch;
		refresh();
		x++;
		switch(ch)
		{
			case 10:
/*				now=time(NULL);
    			tm=localtime(&now);
				sstm <<tm->tm_hour<<":"<<tm->tm_min<<":"<<tm->tm_sec<<" : ";
				s=sstm.str();
				Interface::interface().Write(s.c_str(),1,str);
				memset(&str[0], 0, sizeof(str));
				*/
				Interface::interface().Write("lab1",1,"wiad1");	
				Interface::interface().Write("lab2",1,"wiad2");	
				Interface::interface().Write("lab3",1,"wiad3");	
				Interface::interface().Write("lab4",1,"wiad4");	
				Interface::interface().Write("lab5",1,"wiad5");	
				Interface::interface().Write("lab6",1,"wiad6");	
				x=0;			
				break;
		}
	}
	Interface::interface().deinit();
	return 0;
}
