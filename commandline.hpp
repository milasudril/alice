//@	{
//@	"targets":[{"name":"commandline.hpp","type":"include"}]
//@	}

#ifndef ALICE_COMMANDLINE_HPP
#define ALICE_COMMANDLINE_HPP

#include "optionmap.hpp"
#include "option.hpp"
#include "optionruntime.hpp"
#include <set>
#include <map>

namespace Alice
	{
	template<class OptionDescriptor>
	class CommandLine
		{
		public:
			template<class ErrorHandler>
			CommandLine(int argc,const char* const* argv,ErrorHandler&& eh);

			template<Stringkey::HashValue key>
			auto get() const noexcept
				{return m_entries.get<key>();}

			template<Stringkey::HashValue key>
			auto& get() noexcept
				{return m_entries.get<key>();}

			void valuesPrint() const noexcept
				{
				printf("{");
				auto N=m_entries.size();
				m_entries.itemsEnum([N](size_t index,Stringkey::HashValue key,const auto& x
					,const typename OptionMap<OptionDescriptor>::Paraminfo& paraminfo)
					{
				//	x.valuesPrint();
					if(index + 1!=N)
						{printf(",");}
					});
				printf("}\n");
				}

			void helpPrint(bool headers_print=0) const noexcept
				{
				printf("Command line options\n"
				       "====================\n");
				Stringkey key_prev("");
				
				m_entries.itemsEnum([&key_prev,headers_print]
					(size_t index,Stringkey::HashValue key,const auto& x
					,const typename OptionMap<OptionDescriptor>::Paraminfo& paraminfo)
					{
					auto group_next=Stringkey(paraminfo.group);
				//	paraminfo.print(group_next!=key_prev && headers_print);
				//	x.helpPrint(group_next!=key_prev && headers_print);
					key_prev=group_next;
					});
				}

		private:
			OptionMap<OptionDescriptor> m_entries;
		};

	template<class OptionDescriptor>
	template<class ErrorHandler>
	CommandLine<OptionDescriptor>::CommandLine(int argc,const char* const* argv,ErrorHandler&& eh)
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

		m_entries.itemsEnum([&options,&eh](size_t index,Stringkey::HashValue key,auto& x
			,const typename OptionMap<OptionDescriptor>::Paraminfo& paraminfo)
			{
			auto i=options.find(key);
			if(i!=options.end())
				{
			//	Switch on multiplicity
			//	x.valueSet(make_value(i->second));
				}
			});
		}
	};

#endif