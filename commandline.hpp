//@	{
//@	"targets":[{"name":"commandline.hpp","type":"include"}]
//@	}

#ifndef ALICE_COMMANDLINE_HPP
#define ALICE_COMMANDLINE_HPP

#include "optionmap.hpp"
#include "option.hpp"
#include "optionruntime.hpp"
#include <set>

namespace Alice
	{
	template<class ... entries>
	class CommandLine
		{
		public:
			template<class ErrorHandler>
			CommandLine(ErrorHandler&& eh,int argc,const char* const* argv);

			template<Stringkey::HashValue key>
			auto get() const noexcept
				{return m_entries.get<key>();}

			template<Stringkey::HashValue key>
			auto& get() noexcept
				{return m_entries.get<key>();}

			void valuesPrint() const noexcept
				{m_entries.valuesPrint();}

		private:
			OptionMap<entries...> m_entries;
		};

	template<class ... entries>
	template<class ErrorHandler>
	CommandLine<entries...>::CommandLine(ErrorHandler&& eh,int argc,const char* const* argv)
		{
		std::set<Stringkey::HashValue> keys;
		auto key=m_entries.keysBegin();
		auto keys_end=m_entries.keysEnd();
		while(key!=keys_end)
			{
			keys.insert(*key);
			++key;
			}
		if(argc!=0)
			{
			--argc;
			++argv;
			}

		std::map<Stringkey::HashValue,OptionRuntime> options;
		while(argc!=0)
			{
			OptionRuntime option(*argv);
			auto key=Stringkey(option.nameGet());

			if(keys.find(key)==keys.end())
				{eh.unknownOption(option.nameGet());}

			options.insert({key,std::move(option)});
			++argv;
			--argc;
			}

		m_entries.valuesCollect(options);
		}
	};

#endif