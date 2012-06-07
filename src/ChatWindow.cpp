#include "ChatWindow.hpp"

ChatWindow::ChatWindow()
{
	_win = newwin( LINES-2, 3*COLS/4, 0,0);
	box(_win, 0, 0);
	new_panel(_win);
/*
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
	colourMe=COLOR_PAIR(1);
	colourSb=COLOR_PAIR(2);*/
}

void ChatWindow::Write(int where, char* when, int who, char* what)
{
	//wattron(_win, colourMe);
	mvprintw(where,1,when,_win);
	mvprintw(where,10,what,_win);
	wrefresh(_win);
	//wattroff(_win, colourMe);
}
