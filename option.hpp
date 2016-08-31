//@	{"targets":[{"name":"option.hpp","type":"include"}]}

#ifndef ALICE_OPTION_HPP
#define ALICE_OPTION_HPP

#include <cstddef>
#include <vector>

namespace Alice
	{
	template<class T>
	class Typeinfo;

	template<class Type>
	class Option
		{
		public:
			enum class Multiplicity:size_t{ONE,ONE_OR_MORE};

			explicit constexpr Option(const char* name,const char* description
				,Multiplicity mult):r_name(name),r_description(description)
				,r_name_type(Typeinfo<Type>::name),m_mult(mult)
				{}

			const Type* valuesBegin() const noexcept
				{return values.data();}

			const Type* valuesEnd() const noexcept
				{return values.data() + values.size();}

			void helpPrint() const noexcept;

		private:
			const char* r_name;
			const char* r_description;
			const char* r_name_type;
			Multiplicity m_mult;
			std::vector<Type> values;
		};
	}

#endif