#include "MessagesList.hpp"

MessagesList::MessagesList(){}

void MessagesList::Add(std::string what, std::string when, int who)
{
	messages.push_back(what);
	date.push_back(when);
	user.push_back(who);
	size++;
}
