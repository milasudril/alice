//@	{"targets":[{"name":"optionruntime.o","type":"object"}]}

#include "optionruntime.hpp"

using namespace Alice;

static void optionLoad(std::map<Stringkey::HashValue,std::vector<std::string>>& options
	,const char* arg,CommandLineValidator& validator)
	{
	std::string buffer;
	enum class State:unsigned int
		{
		 START_0,START_1,KEY,VALUE,VALUE_ESCAPE
		};
	auto state=State::START_0;
	std::vector<std::string>* val_current=nullptr;
	std::string name;
	size_t brackets=0;
	Stringkey key("");
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
						validator.syntaxError('-',ch_in);
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
						validator.syntaxError('-',ch_in);
					}
				}
				break;

			case State::KEY:
				{
				switch(ch_in)
					{
					case '=':
						{
						key=Stringkey(buffer.c_str());
						validator.keyValidate(buffer.c_str(),key);
						name=buffer;
						buffer.clear();
						val_current=&options[key];
						state=State::VALUE;
						}
						break;
					case '\0':
						{
						key=Stringkey(buffer.c_str());
						validator.keyValidate(buffer.c_str(),key);
						val_current=&options[key];
						validator.optionValidate(buffer.c_str(),key,val_current->size());
						return;
						}
						break;

					default:
						buffer+=ch_in;
					}
				}
				break;

			case State::VALUE:
				switch(ch_in)
					{
					case '[':
						if(brackets!=0)
							{buffer+=ch_in;}
						++brackets;
						break;
					case ']':
						brackets=brackets==0?0:brackets-1;
						if(brackets!=0)
							{buffer+=ch_in;}
						break;
					case '\\':
						state=State::VALUE_ESCAPE;
						break;
					case ',':
						if(brackets==0)
							{
							val_current->push_back(buffer);
							buffer.clear();
							}
						else
							{buffer+=ch_in;}
						break;
					case '\0':
						val_current->push_back(buffer);
						validator.optionValidate(name.c_str(),key,val_current->size());
						return;
					default:
						buffer+=ch_in;
					}
				break;

			case State::VALUE_ESCAPE:
				if(brackets==0)
					{
					if(ch_in=='\0')
						{
						validator.syntaxError("Command line error: Lonely escape character.");
						}
					buffer+=ch_in;
					}
				else
					{
					if(ch_in!='[' && ch_in!=']')
						{buffer+='\\';}
					buffer+=ch_in;
					}
				state=State::VALUE;
				break;
			}
		++arg;
		}
	}

std::map<Stringkey::HashValue,std::vector<std::string>>
Alice::optionsLoad(int argc,const char* const* argv
	,CommandLineValidator&& validator)
	{
	std::map<Stringkey::HashValue,std::vector<std::string>> ret;
	while(argc!=0)
		{
		optionLoad(ret,*argv,validator);
		--argc;
		++argv;
		}

		return ret;
	}
