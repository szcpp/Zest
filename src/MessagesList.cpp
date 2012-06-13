#include "MessagesList.hpp"

MessagesList::MessagesList(){}

void MessagesList::Add(Message what)
{
	messages.push_back(what);
}
