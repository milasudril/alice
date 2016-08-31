//@	{
//@	 "targets":[{"name":"optionbase.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"optionbase.o","rel":"implementation"}]
//@	}

#ifndef ALICE_OPTIONBASE_HPP
#define ALICE_OPTIONBASE_HPP

#include <cstddef>

namespace Alice
	{
	class OptionBase
		{
		public:
			enum class Multiplicity:size_t
				{ZERO_OR_ONE,ZERO_OR_MORE,ONE,ONE_OR_MORE};

			constexpr OptionBase():r_group(nullptr),r_name(nullptr)
				,r_description(nullptr),r_name_type(nullptr)
				,m_mult(Multiplicity::ZERO_OR_MORE){}

			explicit constexpr OptionBase(const char* group
				,const char* name,const char* description
				,const char* name_type
				,Multiplicity mult):r_group(group),r_name(name)
				,r_description(description),r_name_type(name_type),m_mult(mult)
				{}

			void helpPrint(bool group_header=0) const noexcept;

			constexpr const char* groupGet() const noexcept
				{return r_group;}

		protected:
			void groupHeaderPrint() const noexcept;

			const char* r_group;
			const char* r_name;
			const char* r_description;
			const char* r_name_type;
			Multiplicity m_mult;
		};
	}

#endif
