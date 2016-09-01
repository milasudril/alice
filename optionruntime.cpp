//@	{"targets":[{"name":"optionruntime.o","type":"object"}]}

#include "optionruntime.hpp"

using namespace Alice;

OptionRuntime::OptionRuntime(const char* arg)
	{
	std::string buffer;
	enum class State:unsigned int{START_0,START_1,KEY,VALUE,VALUE_ESCAPE};
	auto state=State::START_0;
	while(true)
		{
		auto ch_in=*arg;
		switch(state)
			{
			case State::START_0:
				{
				switch(ch_in)
					{
					case '-':
						state=State::START_1;
						break;
					default:
						throw "Command line error";
					//	exceptionRaise(ErrorMessage("Command line error: Expected `-` got #0;.",{ch_in}));
					}
				}
				break;

			case State::START_1:
				{
				switch(ch_in)
					{
					case '-':
						state=State::KEY;
						break;
					default:
						throw "Command line error";
					//	exceptionRaise(ErrorMessage("Command line error: Expected `-` got #0;.",{ch_in}));
					}
				}
				break;

			case State::KEY:
				{
				switch(ch_in)
					{
					case '=':
						{
						m_name=buffer;
						buffer.clear();
						state=State::VALUE;
						}
						break;
					case '\0':
						{
						m_name=buffer;
						return;
						}

					default:
						buffer+=ch_in;
					}
				}
				break;

			case State::VALUE:
				switch(ch_in)
					{
					case '\\':
						state=State::VALUE_ESCAPE;
						break;
					case ',':
						m_values.push_back(buffer);
						buffer.clear();
						break;
					case '\0':
						m_values.push_back(buffer);
						return;
					default:
						buffer+=ch_in;
					}
				break;

			case State::VALUE_ESCAPE:
				if(ch_in=='\0')
					{
					throw "Command line error";
				//	exceptionRaise(ErrorMessage("Command line error: Lonely escape character.",{}));
					}
				state=State::VALUE;
				break;
			}
		++arg;
		}
	}
