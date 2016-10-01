//@	{"targets":[{"name":"narrow_cast.hpp","type":"include"}]}

#ifndef ALICE_NARROWCAST_HPP
#define ALICE_NARROWCAST_HPP

#include <limits>

namespace Alice
	{
	template<class T,class ErrorHandler,class U>
	T narrow_cast(const U& x)
		{
		auto x_min=static_cast<U>(std::numeric_limits<T>::min());
		auto x_max=static_cast<U>(std::numeric_limits<T>::max());
		if(x<x_min || x>x_max)
			{
			ErrorHandler::rangeError(x,x_min,x_max);
			}
		return static_cast<T>(x);
		}
	}

#endif
