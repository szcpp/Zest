#include "InputField.hpp"

InputField::InputField()
{
	_win = newwin( 1, COLS, LINES-1,0 );
	new_panel(_win);
}
void InputField::Write(int x, char ch)
{
	mvwaddch(_win,0,x,ch);
	wrefresh(_win);
}
void InputField::Clear()
{
	wclear(_win);
	wrefresh(_win);
}
void InputField::Del(int x)
{
	mvwdelch(_win,0,x-1);
	wrefresh(_win);
}
