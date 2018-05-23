//@	{
//@	"targets":[{"name":"commandline.hpp","type":"include"}]
//@	}

#ifndef ALICE_COMMANDLINE_HPP
#define ALICE_COMMANDLINE_HPP

#include "optionmap.hpp"
#include "optionruntime.hpp"
#include "cmdlineerror.hpp"
#include <set>
#include <map>
#include <cstdio>


#define ALICE_OPTION_DESCRIPTOR(name,...)\
	struct name \
		{ \
		static constexpr Alice::Option options[]={__VA_ARGS__}; \
		}; \
	constexpr const Alice::Option name::options[]

#define ALICE_OPTION_GET(cmdline,key) \
	(cmdline).get<Alice::Stringkey(key)>()

namespace Alice
	{
	template<class OptionDescriptor>
	class CommandLine
		{
		public:
			template<class ErrorHandler=CmdLineError>
			CommandLine(int argc,const char* const* argv);

			template<Stringkey::HashValue key>
			const auto& get() const noexcept
				{return m_entries.template get<key>();}

			template<Stringkey::HashValue key>
			auto& get() noexcept
				{return m_entries.template get<key>();}

			void print(FILE* dest=stdout) const noexcept;

			void help(bool headers_print=0,FILE* dest=stdout) const noexcept;

		private:
			OptionMap<OptionDescriptor> m_entries;
			Array<Option,countof(OptionDescriptor::options)> m_info;

			static constexpr Array<Option,countof(OptionDescriptor::options)> make_info()
				{
				Array<Option,countof(OptionDescriptor::options)> ret{};
				for(decltype(ret.size()) k=0;k<ret.size();++k)
					{ret.data[k]=OptionDescriptor::options[k];}
				return ret;
				}
		};

	template<class Map,class ErrorHandler>
	class KeyChecker:public CommandLineValidator
		{
		public:
			KeyChecker(Map&& map,ErrorHandler& eh)=delete;
			KeyChecker(const Map& map,const Option* options,ErrorHandler& eh):
				r_map(map),r_eh(eh)
				{
				std::set<Stringkey::HashValue> keys;
				auto key=r_map.keysBegin();
				auto keys_end=r_map.keysEnd();
				while(key!=keys_end)
					{
					m_keys.insert({*key,options->multiplicityGet()});
					++options;
					++key;
					}
				}

			void keyValidate(const char* option_name,Stringkey::HashValue key)
				{
				if(m_keys.find(key)==m_keys.end())
					{r_eh.keyError(option_name);}
				}

			void optionValidate(const char* option_name,Stringkey::HashValue key,size_t arg_count)
				{
				auto mult=m_keys.find(key)->second;
				switch(mult)
					{
					case Option::Multiplicity::ZERO_OR_ONE:
						if(arg_count>1)
							{r_eh.optionErrorArgsToMany(option_name,1);}
						break;
					case Option::Multiplicity::ONE:
						if(arg_count>1)
							{r_eh.optionErrorArgsToMany(option_name,1);}
						if(arg_count<1)
							{r_eh.optionErrorArgsToFew(option_name,1);}
						break;
					case Option::Multiplicity::ONE_OR_MORE:
						if(arg_count<1)
							{r_eh.optionErrorArgsToFew(option_name,1);}
						break;
					case Option::Multiplicity::ZERO_OR_MORE:
						break;
					}
				}

			void syntaxError(char ch_good,char ch_bad)
				{r_eh.syntaxError(ch_good,ch_bad);}

			void syntaxError(const char* description)
				{r_eh.syntaxError(description);}

		private:
			const Map& r_map;
			ErrorHandler& r_eh;
			std::map<Stringkey::HashValue,Option::Multiplicity> m_keys;
		};

	template<class OptionDescriptor>
	template<class ErrorHandler>
	CommandLine<OptionDescriptor>::CommandLine(int argc,const char* const* argv)
		:m_info(make_info())
		{
		ErrorHandler eh;
		if(argc==0)
			{return;}

		--argc;
		++argv;

		auto options_loaded=optionsLoad(argc,argv
			,KeyChecker< OptionMap<OptionDescriptor>,ErrorHandler >(m_entries,m_info.data,eh));

		m_entries.itemsEnum([&options_loaded](size_t index,Stringkey::HashValue key,auto& x)
			{
			auto i=options_loaded.find(key);
			if(i!=options_loaded.end())
				{
				typedef typename std::remove_reference<decltype(x)>::type X;
				x.valueSet(make_value<typename X::ValueType,ErrorHandler,X::multi>(i->second));
				}
			});
		}

	template<class OptionDescriptor>
	void CommandLine<OptionDescriptor>::help(bool headers_print,FILE* dest) const noexcept
		{
		fprintf(dest,"Command line options\n"
			"====================\n\n"
			"This is a summary of all command line options. Values inside square brackets "
			"are optional. For details on how to type values, see *Common types* below.\n\n");
		Stringkey key_prev("");
		auto info=m_info.data;
		m_entries.itemsEnum([&key_prev,headers_print,info,dest]
			(size_t index,Stringkey::HashValue key,const auto& x)
			{
			auto group_next=Stringkey(info[index].groupGet());
			info[index].help(group_next!=key_prev && headers_print,dest);
			key_prev=group_next;
			});

		std::map<std::string,std::pair<const char*,const char*>> types;
		m_entries.itemsEnum([info,&types](size_t index,Stringkey::HashValue key,const auto& x)
			{
			typedef typename std::remove_reference<decltype(x)>::type Type;
			auto description_long=MakeType<Type::element_type>::descriptionLongGet();
			auto description_short=MakeType<Type::element_type>::descriptionShortGet();
			if(description_long!=nullptr || description_short!=nullptr)
				{
				types[std::string( info[index].typeGet() )]=
					{description_short,description_long};
				}
			});

		if(types.size()==0) //Do not print anything more if there are no items in type dictionary
			{return;}

		fprintf(dest,"\nCommon types\n"
			"------------\n");
		auto type=types.begin();
		auto type_end=types.end();
		while(type!=type_end)
			{
			fprintf(dest,"\n%s",type->first.c_str());
			if(type->second.first!=nullptr)
				{fprintf(dest," := (%s)",type->second.first);}
			if(type->second.second!=nullptr)
				{fprintf(dest,"\n    %s\n",type->second.second);}
			else
				{putc('\n',dest);}
			++type;
			}
		}

	template<class OptionDescriptor>
	void CommandLine<OptionDescriptor>::print(FILE* dest) const noexcept
		{
		fprintf(dest,"{");
		auto N=m_entries.size();
		auto info=m_info.data;
		m_entries.itemsEnum([N,dest,info]
			(size_t index,Stringkey::HashValue key,const auto& x)
			{
			if(x)
				{
				fprintf(dest,"\"%s\":",info[index].nameGet());
				Alice::print(x.valueGet(),dest);
				if(index + 1!=N)
					{fprintf(dest,"\n,");}
				}
			});
		fprintf(dest,"}\n");
		}
	}

#endif
