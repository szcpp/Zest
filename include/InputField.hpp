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
		/**
			A constructor
		*/
		InputField();
		/**
			Writes into input field single characters
			@param x a position of a character
			@param ch a character to print
		*/
		void Write(int x,char ch);
		/**
			Clears an input field;
		*/
		void Clear();
		/**
			Deletes single character from specific position
			@param x a position of a character to delete increased by one
		*/
		void Del(int x);
	private:
		/**
			Window in which characters are displayed
		*/
		WINDOW* _win;
};

#endif
