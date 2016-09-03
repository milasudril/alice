//@	{"targets":[{"name":"test2","type":"application"}]}

#include "optionmap.hpp"

using namespace Alice;

struct OptionDescriptor
	{
	static constexpr const Option options[]=
		{
			 {"General","help","Prints this message and exits","String",Option::Multiplicity::ZERO_OR_ONE}
			,{"General","a-number","A number","Double",Option::Multiplicity::ONE}
		};
	static constexpr size_t size=2;
	};

constexpr const Option OptionDescriptor::options[];

int main()
	{
	OptionMap<OptionDescriptor> test;

	if(!test.get<Stringkey("help")>())
		{printf("Not set\n");}

	test.get<Stringkey("help")>().valueSet(std::vector<std::string>{"Hello"});
	if(test.get<Stringkey("help")>())
		{printf("Value set\n");}

	test.get<Stringkey("a-number")>().valueSet(3.14);
//	test.get<Stringkey("bad-key")>()="Error";

	return 0;
	}
