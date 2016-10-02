//@	{"targets":[{"name":"test","type":"application"}]}

#include "commandline.hpp"

ALICE_OPTION_DESCRIPTOR(OptionDescriptor
	,{"General","help","Print usage information","string",Alice::Option::Multiplicity::ZERO_OR_ONE}

	,{"Zero or one","do-stuff-a","Perform stuff A","bool",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-b","Perform stuff B","byte",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-c","Perform stuff C","short",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-d","Perform stuff D","int",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-e","Perform stuff E","long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-f","Perform stuff F","long long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-g","Perform stuff G","unsigned byte",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-h","Perform stuff H","unsigned short",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-i","Perform stuff I","unsigned int",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-j","Perform stuff J","unsigned long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-k","Perform stuff k","unsigned long long",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-L","Perform stuff L","float",Alice::Option::Multiplicity::ZERO_OR_ONE}
	,{"Zero or one","do-stuff-M","Perform stuff M","double",Alice::Option::Multiplicity::ZERO_OR_ONE}


	,{"Zero or more","do-stuff-n","Perform stuff N","string",Alice::Option::Multiplicity::ZERO_OR_MORE}
	,{"One","do-stuff-o","Perform stuff O","string",Alice::Option::Multiplicity::ONE}
	,{"One or more","do-stuff-p","Perform stuff P","string",Alice::Option::Multiplicity::ONE_OR_MORE}

	,{"Type alias","do-stuff-q","Perform stuff Q","length",Alice::Option::Multiplicity::ONE_OR_MORE}

	,{"Custom type","do-stuff-r","Perform stuff R","hatter",Alice::Option::Multiplicity::ZERO_OR_MORE}
	);

namespace Alice
	{
	template<>
	struct MakeType<Stringkey("length")>:public MakeType<Stringkey("double")>
		{
		static constexpr const char* descriptionGet() noexcept
			{return "The length measured in meters";}
		};
	}

struct Hatter
	{
	std::string name;
	double madness;
	};

namespace Alice
	{
	template<>
	struct MakeType<Stringkey("hatter")>
		{
		typedef Hatter Type;
		static constexpr const char* descriptionGet() noexcept
			{
			return "A Hatter is entered as a pair `name,madness` where "
				"name is a string, and madness is a value greater than or equal to zero.";
			}
		};

	template<class ErrorHandler>
	struct MakeValue<Hatter,ErrorHandler>
		{
		static Hatter make_value(const std::string& str);
		};

	template<class ErrorHandler>
	Hatter MakeValue<Hatter,ErrorHandler>::make_value(const std::string& str)
		{
		Hatter ret;
		auto ptr=str.data();
		auto count=0;
		std::string buffer;
		while(true)
			{
			auto ch_in=*ptr;
			switch(count)
				{
				case 0:
					switch(ch_in)
						{
						case '\0':
							{
							ErrorMessage msg;
							snprintf(msg.data,msg.size()-1,"The Hatter %s has no madness value",ret.name.c_str());
							msg.data[msg.size()-1]=0;
							throw msg;
							}
							
						case ',':
							++count;
							break;

						default:
							ret.name+=ch_in;
						}

						break;
				case 1:
					switch(ch_in)
						{
						case ',':
							{
							ErrorMessage msg;
							snprintf(msg.data,msg.size()-1,"To many arguments given to the Hatter %s",ret.name.c_str());
							msg.data[msg.size()-1]=0;
							throw msg;
							}
						case '\0':
							ret.madness=Alice::make_value<decltype(Hatter::madness),ErrorHandler>(buffer);
							return ret;
						default:
							buffer+=ch_in;
						}
					break;
				}
			++ptr;
			}
		}

	template<>
	void print<Hatter>(const Hatter& hatter,FILE* dest)
		{
		fprintf(dest,"{\"name\":");
		print(hatter.name,dest);
		fprintf(dest,",\"madness\":");
		print(hatter.madness,dest);
		fprintf(dest,"}\n");
		}
	}

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