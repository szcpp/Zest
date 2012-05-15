#include "Interface.hpp"
Interface* Interface::interface_=NULL;

Interface& Interface::interface()
{
	if(interface_==NULL) interface_=new Interface();
	return *interface_;
}

Interface::Interface()
{
	init();
	signal(SIGWINCH, winchSignalHandler);
}

int Interface::recreate()
{
	deinit();
	init();
	return 1;
}

void Interface::init()
{
	initscr();
	refresh();
	clear();
	// Create windows for the panels
	my_wins[0] = newwin( LINES/2, COLS/2, 0,0);
	my_wins[1] = newwin( LINES/2, COLS/2, 0,COLS/2);
	my_wins[2] = newwin( LINES/2, COLS, LINES/2,0);

	//Create borders around the windows
	for(int i = 0; i < 3; ++i) box(my_wins[i], 0, 0);

	// Attach a panel to each window  	(Order is bottom up)
	my_panels[0] = new_panel(my_wins[0]); 
	my_panels[1] = new_panel(my_wins[1]);
	my_panels[2] = new_panel(my_wins[2]);

	update_panels(); // Update the stacking order. 2nd panel will be on top
	doupdate();	//Show it on the screen
}
void Interface::deinit()
{
	endwin();
}

void Interface::winchSignalHandler(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	Interface::interface().recreate();
	signal(SIGWINCH, winchSignalHandler);
}

int main(int argc, char *argv[])
{
	Interface::interface().init();
	while(getch() != 27) ;
	Interface::interface().deinit();
	return 0;
}
