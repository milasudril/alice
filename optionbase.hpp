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

			constexpr OptionBase():r_group(""),r_name("")
				,r_description(""),r_type_name("")
				,m_mult(Multiplicity::ZERO_OR_MORE),m_valid(0){}

			explicit constexpr OptionBase(const char* group
				,const char* name,const char* description
				,const char* type_name
				,Multiplicity mult):r_group(group),r_name(name)
				,r_description(description),r_type_name(type_name),m_mult(mult),m_valid(0)
				{}

			explicit constexpr OptionBase(const char* group
				,const char* name,const char* description
				,Multiplicity mult):r_group(group),r_name(name)
				,r_description(description),r_type_name(""),m_mult(mult),m_valid(0)
				{}

			void helpPrint(bool group_header=0) const noexcept;

			constexpr const char* groupGet() const noexcept
				{return r_group;}

			bool emptyAllowed() const noexcept
				{
				return m_mult==Multiplicity::ZERO_OR_ONE 
					|| m_mult==Multiplicity::ZERO_OR_MORE;
				}

			bool manyAllowed() const noexcept
				{
				return m_mult==Multiplicity::ZERO_OR_MORE
					|| m_mult==Multiplicity::ONE_OR_MORE;
				}

			bool validIs() const
				{return m_valid;}

		protected:
			void groupHeaderPrint() const noexcept;

			const char* r_group;
			const char* r_name;
			const char* r_description;
			const char* r_type_name;
			Multiplicity m_mult;
			bool m_valid;
		};
	}

#endif
