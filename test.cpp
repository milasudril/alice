//@	{"targets":[{"name":"test","type":"application"}]}

#include "optionmap.hpp"
#include "commandline.hpp"

class CmdLineError
	{
	public:
		static void unknownOption(const char* option_name)
			{
			throw "Unknown option";
			}
	};

int main(int argc,char** argv)
	{
	Alice::OptionMap<
		 Alice::OptionMapEntry<Alice::Stringkey("do-stuff-a"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-b"),Alice::Option<long long int> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-c"),Alice::Option<double> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-d"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-e"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-f"),Alice::Option<std::string> >
		> test;

	test.get<Alice::Stringkey("do-stuff-a")>()={"Zero or one","do-stuff-a","Perform stuff A"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE};
	test.get<Alice::Stringkey("do-stuff-b")>()={"Zero or one","do-stuff-b","Perform stuff B"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE};
	test.get<Alice::Stringkey("do-stuff-c")>()={"Zero or one","do-stuff-c","Perform stuff C"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE};
	test.get<Alice::Stringkey("do-stuff-d")>()={"Zero or more","do-stuff-d","Perform stuff D"
		,Alice::OptionBase::Multiplicity::ZERO_OR_MORE};
	test.get<Alice::Stringkey("do-stuff-e")>()={"One","do-stuff-e","Perform stuff E"
		,Alice::OptionBase::Multiplicity::ONE};
	test.get<Alice::Stringkey("do-stuff-f")>()={"One or more","do-stuff-f","Perform stuff F"
		,Alice::OptionBase::Multiplicity::ONE_OR_MORE};

	test.helpPrint(1);
//	Or without group headers:
//	test.helpPrint(0);

//	Print loaded values as JSON data
	test.valuesPrint();

	Alice::CommandLine<
		 Alice::OptionMapEntry<Alice::Stringkey("do-stuff-a"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-b"),Alice::Option<long long int> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-c"),Alice::Option<double> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-d"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-e"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-f"),Alice::Option<std::string> > >
		cmd_line{CmdLineError(),argc,argv};

	return 0;
	}