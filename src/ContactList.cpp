#include "ContactList.hpp"

ContactList::ContactList()
{
	_win = newwin( LINES-2, COLS-COLS*3/4, 0, 3*COLS/4);
	//box(_win, 0, 0);
	my_items =new ITEM*[100];
	new_panel(_win);
	my_menu=0;
}
void ContactList::CreateList(std::vector<Contact*> contacts)
{
	std::string stat;
	if(my_menu!=0)
	{
		unpost_menu(my_menu);
		free_menu(my_menu);
	}
	for(int i = 0; i < contacts.size(); ++i)
	{
		if(contacts[i]->getStatus() == Contact::AVAILABLE) stat="+";
		else stat="-";
      my_items[i] = new_item(stat.c_str(),contacts[i]->getName().c_str());
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
int ContactList::GetContactNo()
{
	return item_index(my_menu->curitem);
}
