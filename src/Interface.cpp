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

Interface::~Interface()
{
	deinit();
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
void Interface::Write(std::string what)
{
	if(_chatsOpened.size()==0) return;
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
	Message ms;
	ms.content = what;
	ms.type = Message::MESSAGE;
	ms.date = date;
	_chatsOpened[_ActiveChat]->sendMessage(ms);
	_chatsOpened[_ActiveChat]->msgLs.Add(ms);
	if((int)_chatsOpened[_ActiveChat]->msgLs.messages.size()<= LINES-3) _chatWindow->Write(_chatsOpened[_ActiveChat]->msgLs.messages.size()-1, date, 1, what);
	if((int)_chatsOpened[_ActiveChat]->msgLs.messages.size()>LINES-3)
	{
		_chatsOpened[_ActiveChat]->msgLs.chatScroll=_chatsOpened[_ActiveChat]->msgLs.messages.size()-LINES+2;
		recreate();
	}
}
void Interface::rewrite()
{
	if(_chatsOpened.size()==0) return;
	int who;
	_chatWindow->ClearWin();
	for (int it = 0; it != (int)_chatsOpened[_ActiveChat]->msgLs.messages.size(); ++it)
	{
		if(it<_chatsOpened[_ActiveChat]->msgLs.chatScroll) ;
		if(it>=_chatsOpened[_ActiveChat]->msgLs.chatScroll&&it<_chatsOpened[_ActiveChat]->msgLs.chatScroll+LINES-2)
		{
			if(_chatsOpened[_ActiveChat]->msgLs.messages[it].ipAddress == "") who=1;
			else who=2;
			_chatWindow->Write(it-_chatsOpened[_ActiveChat]->msgLs.chatScroll, _chatsOpened[_ActiveChat]->msgLs.messages[it].date, who, _chatsOpened[_ActiveChat]->msgLs.messages[it].content);
		}
	}
	refresh();
}
void Interface::Scroll(int how)
{	
	if(_chatsOpened.size()==0) return;
	if(how<0) if(_chatsOpened[_ActiveChat]->msgLs.chatScroll!=0) _chatsOpened[_ActiveChat]->msgLs.chatScroll+=how;
	if(how>0) if(_chatsOpened[_ActiveChat]->msgLs.messages.size()-_chatsOpened[_ActiveChat]->msgLs.chatScroll>LINES-2) _chatsOpened[_ActiveChat]->msgLs.chatScroll+=how;
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
	if(_contactItems.size()==0) return;
	if(_contactItems[_contactList->GetContactNo()]->getStatus() == Contact::OFFLINE ) return;
	for( auto it = _chatsOpened.begin() ; it != _chatsOpened.end() ; ++it)
		if((*it)->getIp() == _contactItems[_contactList->GetContactNo()] ->getIp())
			return;
	_chatsOpened.push_back( _contactItems[_contactList->GetContactNo()] );
	_chatWindow->ClearWin();
	updatePanels();
	_ActiveChat=_ChatNo;
	_ChatNo++;
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);	
}
void Interface::ChatClose(const std::string &ip)
{
	for( auto it = _chatsOpened.begin() ; it != _chatsOpened.end() ; ++it)
		if((*it)->getIp() == ip)
			_chatsOpened.erase(it);
	_ChatNo--;
	_interfaceIndicator->Clear();
	if(_contactItems.size()==0) return;
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);	
}
int Interface::NewMessageReceived(const std::string &ip)
{
	int i=0;
	//jesli mamy juz otwarty czat z tym kims
	for( auto it = _chatsOpened.begin() ; it != _chatsOpened.end() ; ++it,++i)
		if((*it)->getIp() == ip)
		{
			return i; //kontakt wysle wiadomosc na ekran  do takiego "adresu"
		}
	//jesli nie mamy rozpoczetego czatu 
	_chatWindow->ClearWin();
	updatePanels();
	for(auto it = _contactItems.begin() ; it != _contactItems.end() ; ++it)
		if((*it)->getIp() == ip)
			_chatsOpened.push_back( *it );
	_ActiveChat=_ChatNo;
	_ChatNo++;
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);	
	return _ActiveChat;
}
void Interface::ChangeChat()
{
	if(_chatsOpened.size()==0) return;
	_ActiveChat++;
	_ActiveChat=_ActiveChat%_ChatNo;
	_interfaceIndicator->ChangeTalk(_chatsOpened, _ActiveChat);
	rewrite();
	doupdate();
}
void Interface::AddContact(Contact* contact)
{
	_contactItems.push_back(contact);
	contactListUpdate();
	updatePanels();
	refresh();
}
void Interface::contactListUpdate()
{
	_contactList->CreateList(_contactItems);
	updatePanels();
	refresh();
} 
void Interface::Write(Message* msgRec, int chatNo)
{
	if(_chatsOpened[chatNo]->msgLs.messages.size()<=LINES-3) _chatWindow->Write(_chatsOpened[chatNo]->msgLs.messages.size()-1, msgRec->date, 2, msgRec->content);
	if(_chatsOpened[chatNo]->msgLs.messages.size()>LINES-3)
	{
		_chatsOpened[chatNo]->msgLs.chatScroll=_chatsOpened[chatNo]->msgLs.messages.size()-LINES+2;
		recreate();
	}
}
void Interface::update(P2PConnection* conn)
{
	for(auto it = _contactItems.begin() ; it != _contactItems.end() ; ++it)
		if((*it)->getIp() == conn->getIP())
		{
			(*it)->setConnection(conn);
			conn->addObserver(*it);
			return;
		}
	Contact* contact = new Contact("nowy_uzytkownik", conn->getIP(), false);
	contact->setConnection(conn);
	AddContact(contact);
}
