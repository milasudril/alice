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
	Alice::CommandLine<
		 Alice::OptionMapEntry<Alice::Stringkey("do-stuff-a"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-b"),Alice::Option<long long int> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-c"),Alice::Option<double> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-d"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-e"),Alice::Option<std::string> >
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-f"),Alice::Option<std::string> > >
		cmd_line{{
			 Alice::OptionBase{"Zero or one","do-stuff-a","Perform stuff A",Alice::OptionBase::Multiplicity::ZERO_OR_ONE}
			,Alice::OptionBase{"Zero or one","do-stuff-b","Perform stuff B",Alice::OptionBase::Multiplicity::ZERO_OR_ONE}
			,Alice::OptionBase{"Zero or one","do-stuff-c","Perform stuff C",Alice::OptionBase::Multiplicity::ZERO_OR_ONE}
			,Alice::OptionBase{"Zero or more","do-stuff-d","Perform stuff D",Alice::OptionBase::Multiplicity::ZERO_OR_MORE}
			,Alice::OptionBase{"One","do-stuff-e","Perform stuff E",Alice::OptionBase::Multiplicity::ONE}
			,Alice::OptionBase{"One or more","do-stuff-f","Perform stuff F",Alice::OptionBase::Multiplicity::ONE_OR_MORE}
			},argc,argv,CmdLineError()};
	cmd_line.helpPrint(1);
	cmd_line.valuesPrint();

	return 0;
	}