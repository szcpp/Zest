#include "ChatWindow.hpp"

ChatWindow::ChatWindow()
{
	_win = newwin( LINES-2, 3*COLS/4, 0,0);
	box(_win, 0, 0);
	new_panel(_win);
}

