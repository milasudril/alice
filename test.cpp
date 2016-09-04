//@	{"targets":[{"name":"test","type":"application"}]}

#include "commandline.hpp"

ALICE_OPTION_DESCRIPTOR(OptionDescriptor
	,{"General","help","Print usage information","String",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-a","Perform stuff A","String",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-b","Perform stuff B","Integer",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-c","Perform stuff C","Double",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or more","do-stuff-d","Perform stuff D","String",Alice::Option::Multiplicity::ZERO_OR_MORE}
	,{"One","do-stuff-e","Perform stuff E","String",Alice::Option::Multiplicity::ONE}
	,{"One or more","do-stuff-f","Perform stuff F","String",Alice::Option::Multiplicity::ONE_OR_MORE});

int main(int argc,char** argv)
	{
	try
		{
		Alice::CommandLine<OptionDescriptor> cmd_line{argc,argv};

		if(cmd_line.get<Alice::Stringkey("help")>())
			{
			cmd_line.help(1);
		//	or
		//	cmd_line.helpPrint(0);
		//	to skip headers
			return 0;
			}

	//	This causes compilation error [no key bad-option in the OptionDescriptor]
	//	auto& x=cmd_line.get<Alice::Stringkey("bad-option")>();


		cmd_line.print(stdout);

		return 0;
		}
	catch(const Alice::ErrorMessage& message)
		{
		fprintf(stderr,"%s\n",message.data);
		return -1;
		}
	}