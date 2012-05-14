#ifndef _observer_hpp_
#define _observer_hpp_
/**
	@brief     Observer class.
 	@details   Observer pattern implementation.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
class Observer
{
public:
	Observer();
	virtual ~Observer();
	/**
		Updates itself. Called from Observable.
	*/
	virtual void update() = 0;
};

#endif