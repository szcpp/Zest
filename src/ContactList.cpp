#include "ContactList.hpp"

ContactList::ContactList()
{
	_win = newwin( LINES-2, COLS-COLS*3/4, 0, 3*COLS/4);
	box(_win, 0, 0);
	new_panel(_win);
}
