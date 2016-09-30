//@	{"targets":[{"name":"typeinfo.hpp","type":"include"}]}

#ifndef ALICE_TYPEINFO_HPP
#define ALICE_TYPEINFO_HPP

#include "stringkey.hpp"
#include <string>
#include <vector>

namespace Alice
	{
	template<class Type>
	class Typeinfo
		{
		};

	template<Stringkey::HashValue key>
	struct MakeType
		{};

	template<class Type>
	Type make_value(const std::string& x);




	template<>
	class Typeinfo<long long int>
		{
		public:
			static constexpr const char* name="Integer";
		};

	template<>
	struct MakeType<Stringkey("Integer")>
		{
		public:
			typedef long long int Type;
		};

	inline void print(long long int x,FILE* dest)
		{fprintf(dest,"%lld",x);}

	template<>
	inline long long int make_value<long long int>(const std::string& x)
		{return std::stoll(x);}




	template<>
	struct MakeType<Stringkey("Short integer")>
		{
		public:
			typedef int Type;
		};

	template<>
	class Typeinfo<int>
		{
		public:
			static constexpr const char* name="Short integer";
		};

	inline void print(int x,FILE* dest)
		{fprintf(dest,"%d",x);}

	template<>
	inline int make_value<int>(const std::string& x)
		{return std::stoi(x);}





	template<>
	class Typeinfo<double>
		{
		public:
			static constexpr const char* name="Double";
		};

	inline void print(double x,FILE* dest)
		{fprintf(dest,"%.16e",x);}

	template<>
	inline double make_value<double>(const std::string& x)
		{return std::stod(x);}

	template<>
	struct MakeType<Stringkey("Double")>
		{
		public:
			typedef double Type;
		};



	template<>
	class Typeinfo<std::string>
		{
		public:
			static constexpr const char* name="String";
		};

	inline void print(const std::string& x,FILE* dest)
		{
	//TODO: Escape JSON string!
		fprintf(dest,"\"%s\"",x.c_str());
		}
	
	template<>
	inline std::string make_value<std::string>(const std::string& x)
		{return x;}

	template<>
	struct MakeType<Stringkey("String")>
		{
		public:
			typedef std::string Type;
		};

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

	template<class Type,bool multi>
	struct MakeValueHelper
		{};

	template<class Type>
	struct MakeValueHelper<Type,0>
		{
		static Type make_value(const std::vector<std::string>& x)
			{return Alice::make_value<Type>(x[0]);}
		};

	template<class Type>
	struct MakeValueHelper<Type,1>
		{
		static Type make_value(const std::vector<std::string>& x)
			{
			Type ret;
			auto ptr=x.data();
			auto ptr_end=ptr+x.size();
			while(ptr!=ptr_end)
				{
				ret.push_back(Alice::make_value<typename Type::value_type>(*ptr));
				++ptr;
				}
			return std::move(ret);
			}
		};

	template<class Type,bool multi>
	inline auto make_value(const std::vector<std::string>& x)
		{
		return MakeValueHelper<Type,multi>::make_value(x);
		}
	}

#endif