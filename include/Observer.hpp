#ifndef _Observer_hpp_
#define _Observer_hpp_
/**
	@brief     Observer class.
 	@details   Observer pattern implementation.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      05.2012
 	@copyright GNU Public License.
 */
template <typename T> class Observer
{
public:
	Observer(){};
	virtual ~Observer(){};
	/**
		Updates itself. Called from Observable.
		@param T* a pointer from observable object.
	*/
	virtual void update(T*) = 0;
};

#endif