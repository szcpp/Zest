#include "InterfaceIndicator.hpp"

InterfaceIndicator::InterfaceIndicator()
{
	_win = newwin( 1, COLS, LINES-2,0);
	start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
	wbkgd(_win,COLOR_PAIR(1));
	new_panel(_win);
}

