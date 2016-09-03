//@	{"targets":[{"name":"test2","type":"application"}]}

#include "optionmap2.hpp"

#include "typeinfo.hpp"
#include "optionbase.hpp"

using namespace Alice;

struct OptionDescriptor
	{
	static constexpr const OptionBase options[]=
		{
			 {"General","help","Prints this message and exits","String",OptionBase::Multiplicity::ZERO_OR_ONE}
			,{"General","a-number","A number","Double",OptionBase::Multiplicity::ZERO_OR_ONE}
		};
	static constexpr size_t size=2;
	};

int main()
	{
	OptionMap<OptionDescriptor> test;

	test.get<Stringkey("help")>()="Hello";
	test.get<Stringkey("a-number")>()=3.14;
	test.get<Stringkey("bad-key")>()="Error";

	return 0;
	}
