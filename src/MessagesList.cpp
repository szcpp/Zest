#include "MessagesList.hpp"

MessagesList::MessagesList(){}

void MessagesList::Add(Message what, std::string when, int who)
{
	messages.push_back(what);
	date.push_back(when);
	user.push_back(who);
}
