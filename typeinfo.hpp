//@	{"targets":[{"name":"typeinfo.hpp","type":"include"}]}

#ifndef ALICE_TYPEINFO_HPP
#define ALICE_TYPEINFO_HPP

#include <string>

namespace Alice
	{
	template<class Type>
	class Typeinfo
		{
		};

	template<>
	class Typeinfo<long long int>
		{
		public:
			static constexpr const char* name="Integer";
		};

	void print(long long int x)
		{printf("%lld",x);}

	template<>
	class Typeinfo<double>
		{
		public:
			static constexpr const char* name="Double";
		};

	void print(double x)
		{printf("%.16e",x);}

	template<>
	class Typeinfo<std::string>
		{
		public:
			static constexpr const char* name="String";
		};

	void print(const std::string& x)
		{
	//TODO: Escape JSON string!
		printf("\"%s\"",x.c_str());
		}
	
	}

#endif