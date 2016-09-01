//@	{"targets":[{"name":"option.hpp","type":"include"}]}

#ifndef ALICE_OPTION_HPP
#define ALICE_OPTION_HPP

#include "optionbase.hpp"
#include "typeinfo.hpp"
#include "optionruntime.hpp"

#include <cstddef>
#include <vector>
#include <cstdio>

namespace Alice
	{
	template<class Type>
	class Option:public OptionBase
		{
		public:
			constexpr Option():OptionBase(){}

			constexpr Option(const char* group
				,const char* name,const char* description
				,Multiplicity mult):
				OptionBase(group,name,description,Typeinfo<Type>::name
					,mult)
				{}

			const Type* valuesBegin() const noexcept
				{return values.data();}

			const Type* valuesEnd() const noexcept
				{return values.data() + values.size();}

			void valuesPrint() const noexcept;

			void valuesSet(const OptionRuntime& option);

		private:
			std::vector<Type> values;
		};

	template<class Type>
	void Option<Type>::valuesPrint() const noexcept
		{
		printf("\"%s\":[",r_name);
		auto pos=valuesBegin();
		auto pos_end=valuesEnd();
		while(pos!=pos_end)
			{
			print(*pos);
			++pos;
			if(pos!=pos_end)
				{putchar(',');}
			}
		printf("]\n");
		}

	template<class Type>
	void Option<Type>::valuesSet(const OptionRuntime& option)
		{
		auto pos=option.valuesBegin();
		auto pos_end=option.valuesEnd();
		while(pos!=pos_end)
			{
			values.push_back(make_value<Type>(*pos));
			++pos;
			}
		}
	}

#endif