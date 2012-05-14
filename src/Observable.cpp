#include "Observable.hpp"

void Observable::addObserver(Observer* obs)
{
	_observers.push_back(obs);
}

const void Observable::notifyObservers()
{
	std::vector<Observer*>::iterator it;
	for(it = _observers.begin(); it != _observers.end(); ++it)
		(*it)->update();
}

