#include "InputField.hpp"

InputField::InputField()
{
	_win = newwin( 1, COLS, LINES-1,0 );
	new_panel(_win);
}
