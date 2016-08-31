//@	{
//@	"targets":[{"name":"commandline.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"commandline.o","rel":"implementation"}]
//@	}

#ifndef ALICE_OPTIONS_HPP
#define ALICE_OPTIONS_HPP

#include "option.hpp"

namespace Alice
	{
	class CommandLine
		{
		public:
			CommandLine(int argc,const char* const* argv);

		private:
		};
	};

#endif