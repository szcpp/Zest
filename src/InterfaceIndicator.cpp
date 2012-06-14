#include "InterfaceIndicator.hpp"

InterfaceIndicator::InterfaceIndicator()
{
	_win = newwin( 1, COLS, LINES-2,0);
	start_color();
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
	wbkgd(_win,COLOR_PAIR(5));
	new_panel(_win);
}
void InterfaceIndicator::ChangeTalk(std::vector<Contact*> chats, int active)
{
	int x=0;
	for(std::vector<Contact*>::size_type i = 0; i<chats.size();++i)
	{
		if(i==active) wattron(_win, COLOR_PAIR(5) | A_BOLD );
		else wattron(_win, COLOR_PAIR(5));
		mvwprintw(_win,0,x,(chats[i]->getName()).c_str());
		if(i==active) wattroff(_win, COLOR_PAIR(5) | A_BOLD );
		else wattroff(_win, COLOR_PAIR(5));
		x+=(chats[i]->getName()).size()+1;
	}
	wrefresh(_win);
}
void InterfaceIndicator::Clear()
{
	wclear(_win);
	wrefresh(_win);
}
