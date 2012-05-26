#ifndef _INPUTFIELD_HPP_
#define _INPUTFIELD_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>

/**
	@brief     InputField class.
 	@details   Inheritance from class PANEL. Any message is typed in that field, it handles all the keyboard shortcuts.
 	@author    Anna Zaborowska
 	@version   0.1a
 	@date      26.05.2012
 	@copyright GNU Public License.
 */

class InputField : public PANEL
{
	public:
		InputField();
		void Write(char* str);
	private:
		WINDOW* _win;
};

#endif
