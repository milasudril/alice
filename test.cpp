//@	{"targets":[{"name":"test","type":"application"}]}

#include "commandline.hpp"

ALICE_OPTION_DESCRIPTOR(OptionDescriptor
	,{"General","help","Print usage information","string",Alice::Option::Multiplicity::ZERO_OR_ONE}

	,{"Zero or one","do-stuff-a","Perform stuff A","bool",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-b","Perform stuff B","char",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-c","Perform stuff C","short",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-d","Perform stuff D","int",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-e","Perform stuff E","long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-f","Perform stuff F","long long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-g","Perform stuff G","unsigned char",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-h","Perform stuff H","unsigned short",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-i","Perform stuff I","unsigned int",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-j","Perform stuff J","unsigned long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-k","Perform stuff k","unsigned long long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-L","Perform stuff L","float",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-M","Perform stuff M","double",Alice::Option::Multiplicity::ZERO_OR_ONE}


	,{"Zero or more","do-stuff-n","Perform stuff N","string",Alice::Option::Multiplicity::ZERO_OR_MORE}
	,{"One","do-stuff-o","Perform stuff O","string",Alice::Option::Multiplicity::ONE}
	,{"One or more","do-stuff-p","Perform stuff P","string",Alice::Option::Multiplicity::ONE_OR_MORE});

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
	//	auto& a=cmd_line.get<Alice::Stringkey("bad-option")>();

		auto& x=cmd_line.get<Alice::Stringkey("do-stuff-a")>().valueGet();
		if(x.size()) //This option is zero-or-one, thus an std::vector
			{printf("%d\n",x[0]);}

	//	Alternative syntax (for those who do not like pointy brackets
		auto& y=ALICE_OPTION_GET(cmd_line,"do-stuff-a").valueGet();
		if(y.size())
			{printf("%d\n",y[0]);}

		for(auto&& z: cmd_line.get<Alice::Stringkey("do-stuff-d")>().valueGet())
			{
			printf("%d ",z);
			}
		putchar('\n');

		cmd_line.print(stdout);

		return 0;
		}
	catch(const Alice::ErrorMessage& message)
		{
		fprintf(stderr,"%s\n",message.data);
		return -1;
		}
	}