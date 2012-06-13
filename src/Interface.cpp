#include "Interface.hpp"
#include <unistd.h>

Interface* Interface::_interface=NULL;

Interface& Interface::interface()
{
	if(_interface==NULL) _interface=new Interface();
	return *_interface;
}

Interface::Interface()
{
	init();
	signal(SIGWINCH, winchSignalHandler);
}

void Interface::recreate()
{
	deinit();
	init();
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);
	rewrite();
}

void Interface::init()
{
	initscr();
	refresh();
	clear();
	_contactList = new ContactList();
	_chatWindow=new ChatWindow();
	AddContacts();
	_contactList->CreateList(_contactItems);
	_interfaceIndicator = new InterfaceIndicator();	
	_inputField = new InputField();
	updatePanels();
}
void Interface::updatePanels()
{
	update_panels();
	doupdate();
}
void Interface::deinit()
{
	endwin();
}

void Interface::winchSignalHandler(int sig)
{
	signal(SIGWINCH, SIG_IGN);
	Interface::interface().recreate();
	Interface::interface().rewrite();
	signal(SIGWINCH, winchSignalHandler);
}
void Interface::Write(std::string when, int who, std::string what)
{
	Message ms;
	ms.content = what;
	ms.type = Message::MESSAGE;
	// jakas metoda wysylajaca ms: _contactsConnected[_ActiveChat]._connection->send(ms); ??
	_msg[_ActiveChat].Add(ms,when,who);
	if(_msg[_ActiveChat].messages.size()<=LINES-3) _chatWindow->Write(_msg[_ActiveChat].messages.size()-1, when, 1, what);
	if(_msg[_ActiveChat].messages.size()>LINES-3)
	{
		_ChatScroll[_ActiveChat]=_msg[_ActiveChat].messages.size()-LINES+2;
		recreate();
	}
}
void Interface::rewrite()
{
	_chatWindow->ClearWin();
	for (int it = 0; it != _msg[_ActiveChat].messages.size(); ++it)
	{
		if(it<_ChatScroll[_ActiveChat]) ;
		if(it>=_ChatScroll[_ActiveChat]&&it<_ChatScroll[_ActiveChat]+LINES-2) _chatWindow->Write(it-_ChatScroll[_ActiveChat], _msg[_ActiveChat].date[it], _msg[_ActiveChat].user[it], _msg[_ActiveChat].messages[it].content);
	}
	refresh();
}
void Interface::Scroll(int how)
{
	if(how<0) if(_ChatScroll[_ActiveChat]!=0) _ChatScroll[_ActiveChat]+=how;
	if(how>0) if(_msg[_ActiveChat].messages.size()-_ChatScroll[_ActiveChat]>LINES-2) _ChatScroll[_ActiveChat]+=how;
	recreate();
	updatePanels();
}
void Interface::WriteInput(int x,char ch)
{
	_inputField->Write(x,ch);
}
void Interface::ClearInput()
{
	_inputField->Clear();
}
void Interface::DelInput(int x)
{
	_inputField->Del(x);
}
void Interface::NextContact()
{
	_contactList->GoDown();
}
void Interface::PrevContact()
{
	_contactList->GoUp();
}
void Interface::NewChatInit()
{
	_chatWindow->ClearWin();
	updatePanels();
	_ActiveChat=_ChatNo;
	_ChatNo++;
	_chatsOpened.push_back(*(_contactItems+_contactList->GetContact()));
	/* tu trzeba by dodac nowy obiekt klasy Contact do wektora _contactsConnected */
	//_contactsConnected.push_back(  );
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);	
}
void Interface::NewChatReceive(Message* msgRec)
{
	_chatWindow->ClearWin();
	updatePanels();
	_ActiveChat=_ChatNo;
	_ChatNo++;
//	_chatsOpened.push_back( /* skas mam wziac nazwe kontaktu z Message? ... Tam jest tylko ip :( */ );
	/* tu trzeba by dodac nowy obiekt klasy Contact do wektora _contactsConnected */
	//_contactsConnected.push_back(  );
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);	
}
void Interface::ChangeChat()
{
	_ActiveChat++;
	_ActiveChat=_ActiveChat%_ChatNo;
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);
	rewrite();
	doupdate();
}
void Interface::AddContacts()
{
		*(_contactItems+0)="nowyUser";
		*(_contactItems+1)="User";
		*(_contactItems+2)="nowy";
		*(_contactItems+3)="nowyU";
		*(_contactItems+4)="nowyUs";
}
void Interface::Print(Message* msgRec)
{
	time_t now; 
   struct tm *tm;
	char date[9];
	now=time(NULL);
	tm=localtime(&now);
	date[0] = (tm->tm_hour / 10) + '0' ;
	date[1] = (tm->tm_hour) % 10 + '0';
	date[2] = ':';
	date[3] = (tm->tm_min / 10) + '0' ;
	date[4] = (tm->tm_min) % 10 + '0';
	date[5] = ':';
	date[6] = (tm->tm_sec / 10) + '0' ;
	date[7] = (tm->tm_sec) % 10 + '0';
	date[8] = '\0';
	int Sender=0;
	for(int i=0; i<_ChatNo; i++)
		if(_msg[i].ip == msgRec->ipAddress) Sender=i;
	_msg[Sender].Add(*msgRec,date,2);
	if(_msg[Sender].messages.size()<=LINES-3) _chatWindow->Write(_msg[Sender].messages.size()-1, date, 2, msgRec->content);
	if(_msg[Sender].messages.size()>LINES-3)
	{
		_ChatScroll[Sender]=_msg[Sender].messages.size()-LINES+2;
		recreate();
	}
}
void Interface::update(Message* msgRec)
{
	if(msgRec->type == Message::STATUS_CHANGE_OFFLINE)
	{
		
	} //metoda zmieniajaca status Contactu
	if(msgRec->type == Message::STATUS_CHANGE_AVAILIBLE)
		{} //metoda zmieniajaca status Contactu
	if(msgRec->type == Message::MESSAGE)
	{
		int newChat=0;
		for(int i=0; i<_contactsConnected.size() ; i++)
		{
	//		if(_contactsConnected[i]._connection->getIP()== msgRec->ipAddress)  // inaczej?
			{
				newChat=1;
				Print(msgRec);
			}
		}
		if(newChat==0) NewChatReceive(msgRec);
	}
}

void Interface::update(P2PConnection* conn)
{
	/*  no to jeśli ktoś się połączy - >
								a) czy on rozpoczyna z nami rozmowę ? Wtedy trzeba stworzyć metodę coś jak AddChat() lub wykorzystać ją,
                  		b) czy tylko się dodaje do listy rozmówców -> wtedy trzeba przerobić AddContact()
			 */
	//std::cout << "New connection from" << conn->getIP() << std::endl;
	// nowe polaczenie, podlaczamy sie jako listener nowych wiadomosci!
	for(auto it = _contactItems.begin() ; it != _contactItems.end() ; ++it)
		if(it->getIp() == conn->getIp())
		{
			// przypisanie polaczenia
		}
	conn->addObserver(this);
}
