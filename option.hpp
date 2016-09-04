//@	{
//@	 "targets":[{"name":"option.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"option.o","rel":"implementation"}]
//@	}

#ifndef ALICE_OPTION_HPP
#define ALICE_OPTION_HPP

#include <cstddef>
#include <cstdio>

namespace Alice
	{
	class Option
		{
		public:
			enum class Multiplicity:size_t
				{ZERO_OR_ONE,ZERO_OR_MORE,ONE,ONE_OR_MORE};

			constexpr Option():r_group(""),r_name("")
				,r_description(""),r_type_name("")
				,m_mult(Multiplicity::ZERO_OR_MORE){}

			constexpr Option(const char* group
				,const char* name,const char* description
				,const char* type_name
				,Multiplicity mult):r_group(group),r_name(name)
				,r_description(description),r_type_name(type_name),m_mult(mult)
				{}

			void help(bool group_header=0,FILE* dest=stdout) const noexcept;

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

			constexpr Multiplicity multiplicityGet() const noexcept
				{return m_mult;}

			constexpr const char* nameGet() const noexcept
				{return r_name;}

			constexpr const char* typeGet() const noexcept
				{return r_type_name;}

			constexpr const char* descriptionGet() const noexcept
				{return r_description;}

		protected:
			void groupHeaderPrint(FILE* dest) const noexcept;

			const char* r_group;
			const char* r_name;
			const char* r_description;
			const char* r_type_name;
			Multiplicity m_mult;
		};
	}

#endif
