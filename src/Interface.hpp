#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_
#include <ncurses.h>
#include <panel.h>
#include <signal.h>

/**
	@brief     Interface class.
 	@details   Singleton pattern implementation, ncurses library usage to create windows.
 	@author    Anna Zaborowska
 	@version   0.1a
 	@date      15.05.2012
 	@copyright GNU Public License.
 */

class Interface
{
	public:
		static Interface &interface();
		void init();
		void deinit();
		int recreate();
	private:
		static Interface *interface_;
		Interface();
		WINDOW* my_wins[3];
		PANEL* my_panels[3];
};

void winchSignalHandler(int sig);

#endif
