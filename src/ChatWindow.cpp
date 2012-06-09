#include "ChatWindow.hpp"

ChatWindow::ChatWindow()
{
	_win = newwin( LINES-2, 3*COLS/4, 0,0);
	//box(_win, 0, 0);
	new_panel(_win);

   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
	colourMe=COLOR_PAIR(3);
	colourSb=COLOR_PAIR(2);
}

void ChatWindow::Write(int where, std::string when, int who, std::string what)
{
	wattron(_win, COLOR_PAIR(who+1)| A_BOLD);
	mvwprintw(_win,where,0,when.c_str());
	wattroff(_win, COLOR_PAIR(who+1) | A_BOLD );
	wattron(_win,  COLOR_PAIR(who+2) );
	mvwprintw(_win,where,10,what.c_str());
	wattroff(_win,  COLOR_PAIR(who+2) );
	wrefresh(_win);
}
void ChatWindow::ClearWin()
{
	wclear(_win);
	wrefresh(_win);
}
