//@	{"targets":[{"name":"typeinfo.hpp","type":"include"}]}

#ifndef ALICE_TYPEINFO_HPP
#define ALICE_TYPEINFO_HPP

#include "stringkey.hpp"
#include "narrow_cast.hpp"
#include <string>
#include <vector>
#include <climits>

#define STR(x) #x
#define STRING(x) STR(x)

namespace Alice
	{
	template<Stringkey::HashValue key>
	struct MakeType
		{};

	template<class Type,class ErrorHandler>
	struct MakeValue
		{static Type make_value(const std::string&);};

	template<class Type,class ErrorHandler>
	Type make_value(const std::string& x)
		{return MakeValue<Type,ErrorHandler>::make_value(x);}

	template<class ErrorHandler>
	unsigned long long int toUint(const std::string& str)
		{
		char* ptr_end;
		auto ret=strtoull(str.c_str(), &ptr_end, 10);
		if(errno==ERANGE)
			{
			ErrorHandler::rangeError(std::numeric_limits<unsigned long long>::min()	
				,std::numeric_limits<unsigned long long>::max());
			}
		return ret;
		}

	template<class ErrorHandler>
	long long int toInt(const std::string& str)
		{
		char* ptr_end;
		auto ret=strtoll(str.c_str(), &ptr_end, 10);
		if(errno==ERANGE)
			{
			ErrorHandler::rangeError(std::numeric_limits<long long>::min()	
				,std::numeric_limits<long long>::max());
			}
		return ret;
		}


//# Predefined types
//# ================
//#	These types are predefined by Alice. It is likely that the caller wants
//#	to create type aliases for more descriptive and less technical names.
//#	For example, it may be better to use the type `distance` instead of
//#	`double`. See [Creating a type alias] for details.


//# The bool type
//# -------------
//# The bool type can be converted from true/false, yes/no, or a numerical
//#	value

	template<>
	struct MakeType<Stringkey("bool")>
		{
		typedef bool Type;
		static constexpr const char* description=
			"can be true, false, yes, or no. "
			"`true` is equivalent to `yes` and `false` is equivalent to no. "
			"It is also possible to use a number. In this case, any non-zero value is "
			"`true` and zero is `false`.";
		};

	inline void print(bool x,FILE* dest)
		{fprintf(dest,"%s",x?"true":"false");}

	template<class ErrorHandler>
	struct MakeValue<bool,ErrorHandler>
		{
		static bool make_value(const std::string& x)
			{
			if(x=="true" || x=="yes")
				{return 1;}
			if(x=="false" || x=="no")
				{return 0;}
			return toUint<ErrorHandler>(x);
			}
		};


//#	Signed integers
//#	---------------
//#	Signed integers uses the raw C++ types. `char` is assumed to be an 
//#	one byte integer, because it is unlikely that a one byte string is
//#	ever used.

	template<>
	struct MakeType<Stringkey("byte")>
		{
		typedef char Type;
		static constexpr const char* description=
			"An integer in the range [" STRING(SCHAR_MIN) ", " STRING(SCHAR_MAX) "]";
		};

	inline void print(char x,FILE* dest)
		{fprintf(dest,"%d",x);}

	template<class ErrorHandler>
	struct MakeValue<char,ErrorHandler>
		{
		static char make_value(const std::string& x)
			{return narrow_cast<char,ErrorHandler>( toInt<ErrorHandler>(x) );}
		};


	template<>
	struct MakeType<Stringkey("short")>
		{
		typedef short Type;
		static constexpr const char* description=
			"An integer in the range [" STRING(SHRT_MIN) ", " STRING(SHRT_MAX) "]";
		};

	inline void print(short x,FILE* dest)
		{fprintf(dest,"%d",x);}

	template<class ErrorHandler>
	struct MakeValue<short,ErrorHandler>
		{
		static short make_value(const std::string& x)
			{return narrow_cast<short,ErrorHandler>( toInt<ErrorHandler>(x) );}
		};


	template<>
	struct MakeType<Stringkey("int")>
		{
		typedef int Type;
		static constexpr const char* description=
			"An integer in the range [" STRING(INT_MIN) ", " STRING(INT_MAX) "]";
		};

	inline void print(int x,FILE* dest)
		{fprintf(dest,"%d",x);}

	template<class ErrorHandler>
	struct MakeValue<int,ErrorHandler>
		{
		static int make_value(const std::string& x)
			{return narrow_cast<int,ErrorHandler>(toInt<ErrorHandler>(x));}
		};


	template<>
	struct MakeType<Stringkey("long")>
		{
		typedef long Type;
		static constexpr const char* description=
			"An integer in the range [" STRING(LONG_MIN) ", " STRING(LONG_MAX) "]";
		};

	inline void print(long int x,FILE* dest)
		{fprintf(dest,"%ld",x);}

	template<class ErrorHandler>
	struct MakeValue<long,ErrorHandler>
		{
		static long make_value(const std::string& x)
			{return narrow_cast<long,ErrorHandler>(toInt<ErrorHandler>(x));}
		};


	template<>
	struct MakeType<Stringkey("long long")>
		{
		typedef long long Type;
		static constexpr const char* description=
			"An integer in the range [" STRING(LLONG_MIN) ", " STRING(LLONG_MAX) "]";
		};

	inline void print(long long int x,FILE* dest)
		{fprintf(dest,"%lld",x);}

	template<class ErrorHandler>
	struct MakeValue<long long,ErrorHandler>
		{
		static long long make_value(const std::string& x)
			{return toInt<ErrorHandler>(x);}
		};


//#	Unsigned integers
//#	-----------------
//#	Unsigned integers uses the raw C++ types. `unsigend char` is assumed to be
//# an one byte integer, because it is unlikely that a one byte string is ever
//#	used.

	template<>
	struct MakeType<Stringkey("unsigned byte")>
		{
		typedef unsigned char Type;
		static constexpr const char* description=
			"An integer in the range [0, " STRING(UCHAR_MAX) "]";
		};

	inline void print(unsigned char x,FILE* dest)
		{fprintf(dest,"%u",x);}

	template<class ErrorHandler>
	struct MakeValue<unsigned char,ErrorHandler>
		{
		static unsigned char make_value(const std::string& x)
			{return narrow_cast<unsigned char,ErrorHandler>( toInt<ErrorHandler>(x) );}
		};


	template<>
	struct MakeType<Stringkey("unsigned short")>
		{
		typedef unsigned short Type;
		static constexpr const char* description=
			"An integer in the range [0, " STRING(USHRT_MAX) "]";
		};

	inline void print(unsigned short x,FILE* dest)
		{fprintf(dest,"%u",x);}

	template<class ErrorHandler>
	struct MakeValue<unsigned short,ErrorHandler>
		{
		static unsigned short make_value(const std::string& x)
			{return narrow_cast<unsigned short,ErrorHandler>( toInt<ErrorHandler>(x) );}
		};


	template<>
	struct MakeType<Stringkey("unsigned int")>
		{
		typedef unsigned int Type;
		static constexpr const char* description=
			"An integer in the range [0, " STRING(UINT_MAX) "]";
		};

	inline void print(unsigned int x,FILE* dest)
		{fprintf(dest,"%u",x);}

	template<class ErrorHandler>
	struct MakeValue<unsigned int,ErrorHandler>
		{
		static unsigned int make_value(const std::string& x)
			{return narrow_cast<unsigned int,ErrorHandler>( toInt<ErrorHandler>(x) );}
		};


	template<>
	struct MakeType<Stringkey("unsigned long")>
		{
		typedef unsigned long Type;
		static constexpr const char* description=
			"An integer in the range [0, " STRING(ULONG_MAX) "]";
		};

	inline void print(unsigned long x,FILE* dest)
		{fprintf(dest,"%lu",x);}

	template<class ErrorHandler>
	struct MakeValue<unsigned long,ErrorHandler>
		{
		static unsigned long make_value(const std::string& x)
			{
			return narrow_cast<unsigned long,ErrorHandler>( toInt<ErrorHandler>(x) );
			}
		};


	template<>
	struct MakeType<Stringkey("unsigned long long")>
		{
		typedef unsigned long long Type;
		static constexpr const char* description=
			"An integer in the range [0, " STRING(ULLONG_MAX) "]";
		};

	inline void print(unsigned long long x,FILE* dest)
		{fprintf(dest,"%llu",x);}

	template<class ErrorHandler>
	struct MakeValue<unsigned long long,ErrorHandler>
		{
		static unsigned long long make_value(const std::string& x)
			{
			return toUint<ErrorHandler>(x);
			}
		};


//#	Floating point types
//#	--------------------

	template<>
	struct MakeType<Stringkey("float")>
		{
		typedef double Type;
		static constexpr const char* description=
			"A floating point value, single precision";
		};

	inline void print(float x,FILE* dest)
		{fprintf(dest,"%.8e",x);}

	template<class ErrorHandler>
	struct MakeValue<float,ErrorHandler>
		{
		static float make_value(const std::string& x)
			{return std::stof(x);}
		};


	template<>
	struct MakeType<Stringkey("double")>
		{
		typedef double Type;
		static constexpr const char* description=
			"A floating point value, double precision";
		};

	inline void print(double x,FILE* dest)
		{fprintf(dest,"%.16e",x);}

	template<class ErrorHandler>
	struct MakeValue<double,ErrorHandler>
		{
		static float make_value(const std::string& x)
			{return std::stod(x);}
		};


//#	std::string
//#	--------------------

	template<>
	struct MakeType<Stringkey("string")>
		{
		typedef std::string Type;
		static constexpr const char* description=
			"An UTF-8 encoded string";
		};

	inline void print(const std::string& x,FILE* dest)
		{
	//TODO: Escape JSON string!
		fprintf(dest,"\"%s\"",x.c_str());
		}

	template<class ErrorHandler>
	struct MakeValue<std::string,ErrorHandler>
		{
		static std::string make_value(const std::string& x)
			{return x;}
		};


//#	Array stuff
//# -----------	

	template<class T>
	inline void print(const std::vector<T>& values,FILE* dest)
		{
		auto ptr=values.data();
		auto ptr_end=ptr+values.size();
		fprintf(dest,"[");
		if(ptr!=ptr_end)
			{
			print(*ptr,dest);
			++ptr;
			}
		while(ptr!=ptr_end)
			{
			fprintf(dest,",");
			print(*ptr,dest);
			++ptr;
			}
		fprintf(dest,"]");
		}

	template<>
	inline void print<bool>(const std::vector<bool>& values,FILE* dest)
		{
		auto ptr=values.begin();
		auto ptr_end=values.end();
		fprintf(dest,"[");
		if(ptr!=ptr_end)
			{
			print(*ptr,dest);
			++ptr;
			}
		while(ptr!=ptr_end)
			{
			fprintf(dest,",");
			print(*ptr,dest);
			++ptr;
			}
		fprintf(dest,"]");
		}

	template<class Type,class ErrorHandler,bool multi>
	struct MakeValueHelper
		{};

	template<class Type,class ErrorHandler>
	struct MakeValueHelper<Type,ErrorHandler,0>
		{
		static Type make_value(const std::vector<std::string>& x)
			{return Alice::make_value<Type,ErrorHandler>(x[0]);}
		};

	template<class Type,class ErrorHandler>
	struct MakeValueHelper<Type,ErrorHandler,1>
		{
		static Type make_value(const std::vector<std::string>& x)
			{
			Type ret;
			auto ptr=x.data();
			auto ptr_end=ptr+x.size();
			while(ptr!=ptr_end)
				{
				ret.push_back(Alice::make_value<typename Type::value_type,ErrorHandler>(*ptr));
				++ptr;
				}
			return std::move(ret);
			}
		};

	template<class Type,class ErrorHandler,bool multi>
	inline auto make_value(const std::vector<std::string>& x)
		{return MakeValueHelper<Type,ErrorHandler,multi>::make_value(x);}
	}

#endif