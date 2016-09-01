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

	template<class Type>
	Type make_value(const std::string& x);

	template<>
	class Typeinfo<long long int>
		{
		public:
			static constexpr const char* name="Integer";
		};

	void print(long long int x)
		{printf("%lld",x);}

	template<>
	long long int make_value<long long int>(const std::string& x)
		{return std::stoll(x);}

	template<>
	class Typeinfo<double>
		{
		public:
			static constexpr const char* name="Double";
		};

	void print(double x)
		{printf("%.16e",x);}

	template<>
	double make_value<double>(const std::string& x)
		{return std::stod(x);}

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
	
	template<>
	std::string make_value<std::string>(const std::string& x)
		{return x;}
	}

#endif