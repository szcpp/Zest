#include "Interface.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	Interface::interface().init();
	keypad(stdscr, TRUE);
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
		if(ch== KEY_UP) {Interface::interface().Scroll(-1);}
		else
		{
			if(ch== KEY_DOWN) {Interface::interface().Scroll(1);}
			else
			{
				str[x]=ch;
				refresh();
				x++;
			}
		}
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
				Interface::interface().Write("lab7",1,"wiad7");	
				Interface::interface().Write("lab8",1,"wiad8");	
				Interface::interface().Write("lab9",1,"wiad9");	
				Interface::interface().Write("lab10",1,"wiad10");	
				Interface::interface().Write("lab11",1,"wiad11");	
				Interface::interface().Write("lab12",1,"wiad12");	
				Interface::interface().Write("lab13",1,"wiad13");	
				Interface::interface().Write("lab14",1,"wiad14");	
				Interface::interface().Write("lab15",1,"wiad15");	
				Interface::interface().Write("lab16",1,"wiad16");		
				Interface::interface().Write("lab17",1,"wiad17");	
				Interface::interface().Write("lab18",1,"wiad18");	
				Interface::interface().Write("lab19",1,"wiad19");	
				Interface::interface().Write("lab20",1,"wiad20");	
				Interface::interface().Write("lab21",1,"wiad21");	
				Interface::interface().Write("lab22",1,"wiad22");	
				Interface::interface().Write("lab23",1,"wiad23");	
				Interface::interface().Write("lab24",1,"wiad24");	
				Interface::interface().Write("lab25",1,"wiad25");	
				Interface::interface().Write("lab26",1,"wiad26");		
				Interface::interface().Write("lab27",1,"wiad27");	
				Interface::interface().Write("lab28",1,"wiad28");	
				Interface::interface().Write("lab29",1,"wiad29");	
				x=0;			
				break;
		}
	}
	Interface::interface().deinit();
	return 0;
}
