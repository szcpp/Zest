#include "ContactList.hpp"

ContactList::ContactList()
{
	_win = newwin( LINES-2, COLS-COLS*3/4, 0, 3*COLS/4);
	//box(_win, 0, 0);
	my_items =new ITEM*[100];
	new_panel(_win);
}
void ContactList::CreateList(std::string* choices)
{
	for(int i = 0; i < 10; ++i)
	{
      my_items[i] = new_item(choices[i].c_str(), "");
	}
	my_menu = new_menu((ITEM **)my_items);

   set_menu_win(my_menu, _win);
   post_menu(my_menu);
	wrefresh(_win);
}
void ContactList::GoDown()
{
	menu_driver(my_menu, REQ_DOWN_ITEM);
	wrefresh(_win);
}

void ContactList::GoUp()
{
	menu_driver(my_menu, REQ_UP_ITEM);
	wrefresh(_win);
}
int ContactList::GetContact()
{
	return item_index(my_menu->curitem);
}
