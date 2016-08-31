//@	{
//@	 "targets":[{"name":"optionruntime.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"optionruntime.o","rel":"implementation"}]
//@	}

#ifndef ALICE_COMMANDLINEBASE_HPP
#define ALICE_COMMANDLINEBASE_HPP

#include "stringkey.hpp"
#include <string>
#include <vector>

namespace Alice
	{
	class OptionRuntime
		{
		public:
			OptionRuntime(const char* arg_value);

			const Stringkey& keyGet() const noexcept
				{return m_key;}

			std::vector<std::string> valuesGet()
				{return std::move(m_values);}

			const char* nameGet() const noexcept
				{return m_name.c_str();}

		private:
			std::string m_name;
			Stringkey m_key;
			std::vector<std::string> m_values;
		};
	};

#endif