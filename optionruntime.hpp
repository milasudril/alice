//@	{
//@	 "targets":[{"name":"optionruntime.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"optionruntime.o","rel":"implementation"}]
//@	}

#ifndef ALICE_OPTIONRUNTIME_HPP
#define ALICE_OPTIONRUNTIME_HPP

#include "stringkey.hpp"
#include <string>
#include <vector>
#include <map>

namespace Alice
	{
	class CommandLineValidator
		{
		public:
			virtual void keyValidate(const char* option_name,Stringkey::HashValue key)=0;
			virtual void optionValidate(const char* option_name,Stringkey::HashValue key,size_t arg_count)=0;
			virtual void syntaxError(char ch_good,char ch_badcl)=0;
			virtual void syntaxError(const char* description)=0;
		};

	std::map<Stringkey::HashValue,std::vector<std::string>> optionsLoad(int argc,const char* const* argv
		,CommandLineValidator&& validator);
	};

#endif
