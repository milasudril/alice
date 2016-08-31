//@	{"targets":[{"name":"test","type":"application"}]}

#include "option.hpp"
#include "optionmap.hpp"
#include "stringkey.hpp"
#include <string>

int main()
	{
	Alice::Option<std::string> a("Zero or one","do-stuff-a","Perform stuff A"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE);

	Alice::Option<long long int> b("Zero or one","do-stuff-b","Perform stuff B"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE);

	Alice::Option<double> c("Zero or one","do-stuff-c","Perform stuff C"
		,Alice::OptionBase::Multiplicity::ZERO_OR_ONE);


	Alice::Option<std::string> d("Zero or more","do-stuff-d","Perform stuff D"
		,Alice::OptionBase::Multiplicity::ZERO_OR_MORE);

	Alice::Option<std::string> e("One","do-stuff-e","Perform stuff E"
		,Alice::OptionBase::Multiplicity::ONE);

	Alice::Option<std::string> f("One or more","do-stuff-f","Perform stuff F"
		,Alice::OptionBase::Multiplicity::ONE_OR_MORE);

	Alice::OptionMap<
		 Alice::OptionMapEntry<Alice::Stringkey("do-stuff-a"),decltype(a)>
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-b"),decltype(b)>
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-c"),decltype(c)>
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-d"),decltype(d)>
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-e"),decltype(e)>
		,Alice::OptionMapEntry<Alice::Stringkey("do-stuff-f"),decltype(f)>
		> test;

	test.get<Alice::Stringkey("do-stuff-a")>()=a;
	test.get<Alice::Stringkey("do-stuff-b")>()=b;
	test.get<Alice::Stringkey("do-stuff-c")>()=c;
	test.get<Alice::Stringkey("do-stuff-d")>()=d;
	test.get<Alice::Stringkey("do-stuff-e")>()=e;
	test.get<Alice::Stringkey("do-stuff-f")>()=f;

	test.helpPrint(1);
//	Or without group headers:
//	test.helpPrint(0);

//	Print loaded values as JSON data
	test.valuesPrint();
	return 0;
	}