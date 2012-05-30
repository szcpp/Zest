#include "Interface.hpp"

int main(int argc, char *argv[])
{
	Interface::interface().init();
	while(getch() != 27) ;
	Interface::interface().deinit();
	return 0;
}
