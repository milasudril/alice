//@	{"targets":[{"name":"cmdlineerror.hpp","type":"include"}]}

#ifndef ALICE_CMDLINEERROR_HPP
#define ALICE_CMDLINEERROR_HPP

namespace Alice
	{
	typedef Array<char,512> ErrorMessage;

	class CmdLineError
		{
		public:
			static void keyError(const char* option_name)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Command line error: Unknown option %s",option_name);
				message.data[511]=0;
				throw message;
				}

			static void optionErrorArgsToFew(const char* option_name,size_t arg_count)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Command line error: Option %s requires at least %zu arguments"
					,option_name,arg_count);
				message.data[511]=0;
				throw message;
				}

			static void optionErrorArgsToMany(const char* option_name,size_t arg_count)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Command line error: Option %s takes at most %zu arguments"
					,option_name,arg_count);
				message.data[511]=0;
				throw message;
				}

			static void syntaxError(char ch_good,char ch_bad)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Command line error: Invalid character. Got `%c`, expected `%c`"
					,ch_bad,ch_good);
				message.data[511]=0;
				throw message;
				}

			static void syntaxError(const char* description)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Command line error: %s",description);
				message.data[511]=0;
				throw message;
				}
		};
	}
#endif
