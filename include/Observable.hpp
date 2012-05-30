#ifndef _Observable_hpp_
#define _Observable_hpp_
#include <vector>
#include "Observer.hpp"

/**
	@brief     Observable class.
 	@details   Observer pattern implementation.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class Observable
{
public:
	Observable(){};
	virtual ~Observable(){};

	/**
		Updates itself. Called from Observable.
		@param obs Observer object.
		@see Observer
	*/
	void addObserver(Observer* obs);

	/**
		Notifies all observers about change.
		@see Observer
	*/
	const void notifyObservers();
private:
	std::vector<Observer*> _observers;
};

#endif