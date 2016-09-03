//@	{"targets":[{"name":"option.o","type":"object"}]}

#include "option.hpp"
#include <cstdio>

using namespace Alice;

void Option::helpPrint(bool group_header) const noexcept
	{
	if(group_header)
		{groupHeaderPrint();}

	printf("--%s",r_name);
	switch(m_mult)
		{
		case Multiplicity::ZERO_OR_ONE:
			printf("[=%s]",r_type_name);
			break;
		case Multiplicity::ZERO_OR_MORE:
			printf("[=%s,...]",r_type_name);
			break;
		case Multiplicity::ONE:
			printf("=%s",r_type_name);
			break;
		case Multiplicity::ONE_OR_MORE:
			printf("=%s,...",r_type_name);
			break;
		}
	printf("\n    %s\n\n",r_description);
	}

void Option::groupHeaderPrint() const noexcept
	{
	printf("\n%s\n",r_group);
	auto x=r_group;
	while(*x!='\0')
		{
		putchar('-');
		++x;
		}
	printf("\n\n");
	}
