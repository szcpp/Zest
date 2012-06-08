#ifndef _INPUTFIELD_HPP_
#define _INPUTFIELD_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>

/**
	@brief     InputField class.
 	@details   Inheritance from class PANEL. Any message is typed in that field, it handles all the keyboard shortcuts.
 	@author    Anna Zaborowska
 	@version   0.1b
 	@date      08.06.2012
 	@copyright GNU Public License.
 */

class InputField : public PANEL
{
	public:
		InputField();
		void Write(int x,char ch);
		void Clear();
		void Del(int x);
		WINDOW* _win;
	private:
};

#endif
