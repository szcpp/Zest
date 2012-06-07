#ifndef _Observable_hpp_
#define _Observable_hpp_
#include <vector>
#include <iostream>
#include "Observer.hpp"

/**
	@brief     Observable class.
 	@details   Observer pattern implementation.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
template <typename T> class Observable
{
public:
	Observable(){};
	virtual ~Observable(){};

	/**
		Updates itself. Called from Observable.
		@param obs Observer object.
		@see Observer
	*/
	void addObserver(Observer<T>* obs)
	{
		_observers.push_back(obs);
	}

	/**
		Notifies all observers about change.
		@param T* a pointer being passed to all observers
		@see Observer
	*/
	const void notifyObservers(T* data)
	{
		for(auto it = _observers.begin(); it != _observers.end(); ++it)
			(*it)->update(data);
	}
private:
	std::vector<Observer<T>* > _observers;
};

#endif