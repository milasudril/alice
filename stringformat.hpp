//@	{"targets":[{"name":"stringformat.hpp","type":"include"}]}

#ifndef ALICE_STRINGFORMAT_HPP
#define ALICE_STRINGFORMAT_HPP

#include "array.hpp"
#include <type_traits>

namespace
	{
	template<class T,class U>
	struct ToString
		{
		};

	template<class T,T n>
	struct ToString< T,std::integral_constant<T,n> >
		{
		template<std::enable_if_t< std::is_signed<T>::value >* dummy=nullptr>
		static constexpr auto toString()
			{
			constexpr const char* digits="0123456789";
			return Alice::append(ToString< T,std::integral_constant<T,n/10> >::toString(),digits[-(n%10)]);
			}

		template<std::enable_if_t< std::is_unsigned<T>::value >* dummy=nullptr>
		static constexpr auto toString()
			{
			constexpr const char* digits="0123456789";
			return Alice::append(ToString< T,std::integral_constant<T,n/10> >::toString(),digits[n%10]);
			}
		};

	template<class T>
	struct ToString<T, std::integral_constant<T,static_cast<T>(0) > >
		{
		static constexpr Alice::Array<char,0> toString()
			{return Alice::Array<char,0>{};}
		};
	}


namespace Alice
	{
	template<class T,T n,std::enable_if_t< (n>0) && std::is_signed<T>::value >* dummy=nullptr>
	auto constexpr toString()
		{
		return ToString< T,std::integral_constant<T,-n> >::toString();
		}

	template<class T,T n,std::enable_if_t< std::is_unsigned<T>::value && n!=0 >* dummy=nullptr>
	auto constexpr toString()
		{
		return ToString< T,std::integral_constant<T,n> >::toString();
		}

	template<class T,T n,std::enable_if_t<n==0>* dummy=nullptr>
	auto constexpr toString()
		{return Array<char,1>{'0'};}

	template<class T,T n,std::enable_if_t< (n<0) >* dummy=nullptr>
	auto constexpr toString()
		{
		return append('-',ToString< T,std::integral_constant<T,n> >::toString());
		}
	}

#endif