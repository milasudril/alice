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

			const std::vector<std::string>& valuesGet() const noexcept
				{return m_values;}

			const char* nameGet() const noexcept
				{return m_name.c_str();}

			const std::string* valuesBegin() const noexcept
				{return m_values.data();}

			const std::string* valuesEnd() const noexcept
				{return m_values.data() + m_values.size();}

		private:
			std::string m_name;
			std::vector<std::string> m_values;
		};
	};

#endif