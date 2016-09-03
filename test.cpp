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

struct OptionDescriptor
	{
	static constexpr const Alice::Option options[]=
		{
		 {"General","help","Print usage information","String",Alice::Option::Multiplicity::ZERO_OR_ONE}
		,{"Zero or one","do-stuff-a","Perform stuff A","String",Alice::Option::Multiplicity::ZERO_OR_ONE}
		,{"Zero or one","do-stuff-b","Perform stuff B","Integer",Alice::Option::Multiplicity::ZERO_OR_ONE}
		,{"Zero or one","do-stuff-c","Perform stuff C","Double",Alice::Option::Multiplicity::ZERO_OR_ONE}
		,{"Zero or more","do-stuff-d","Perform stuff D","String",Alice::Option::Multiplicity::ZERO_OR_MORE}
		,{"One","do-stuff-e","Perform stuff E","String",Alice::Option::Multiplicity::ONE}
		,{"One or more","do-stuff-f","Perform stuff F","String",Alice::Option::Multiplicity::ONE_OR_MORE}
		};
	static constexpr const size_t size=7;
	};

constexpr const Alice::Option OptionDescriptor::options[];

int main(int argc,char** argv)
	{
	Alice::CommandLine<OptionDescriptor>
		cmd_line{argc,argv,CmdLineError()};

	if(cmd_line.get<Alice::Stringkey("help")>())
		{
		cmd_line.helpPrint(1);
	//	or
	//	cmd_line.helpPrint(0);
	//	to skip headers
		return 0;
		}

//	This causes compile-time error [no key bad-option]
//	auto& x=cmd_line.get<Alice::Stringkey("bad-option")>();


	cmd_line.valuesPrint();

	return 0;
	}