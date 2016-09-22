//@	{"targets":[{"name":"option.o","type":"object"}]}

#include "option.hpp"
#include <cstdio>

using namespace Alice;

void Option::help(bool group_header,FILE* dest) const noexcept
	{
	if(group_header)
		{groupHeaderPrint(dest);}

	fprintf(dest,"--%s",r_name);
	switch(m_mult)
		{
		case Multiplicity::ZERO_OR_ONE:
			fprintf(dest,"[=%s]",r_type_name);
			break;
		case Multiplicity::ZERO_OR_MORE:
			fprintf(dest,"[=%s,...]",r_type_name);
			break;
		case Multiplicity::ONE:
			fprintf(dest,"=%s",r_type_name);
			break;
		case Multiplicity::ONE_OR_MORE:
			fprintf(dest,"=%s,...",r_type_name);
			break;
		}
	fprintf(dest,"\n    %s\n\n",r_description);
	}

void Option::groupHeaderPrint(FILE* dest) const noexcept
	{
	fprintf(dest,"\n%s\n",r_group);
	auto x=r_group;
	while(*x!='\0')
		{
		putc('-',dest);
		++x;
		}
	fprintf(dest,"\n\n");
	}
