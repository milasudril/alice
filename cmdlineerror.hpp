//@	{"targets":[{"name":"cmdlineerror.hpp","type":"include"}]}

#ifndef ALICE_CMDLINEERROR_HPP
#define ALICE_CMDLINEERROR_HPP

#include <type_traits>

namespace Alice
	{
	typedef Array<char,512> ErrorMessage;

	class CmdLineError
		{
		public:
			static void keyError(const char* option_name)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Unknown option %s",option_name);
				message.data[511]=0;
				throw message;
				}

			static void optionErrorArgsToFew(const char* option_name,size_t arg_count)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Option %s requires at least %zu arguments"
					,option_name,arg_count);
				message.data[511]=0;
				throw message;
				}

			static void optionErrorArgsToMany(const char* option_name,size_t arg_count)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Option %s takes at most %zu arguments"
					,option_name,arg_count);
				message.data[511]=0;
				throw message;
				}

			static void syntaxError(char ch_good,char ch_bad)
				{
				ErrorMessage message;
				snprintf(message.data,512,"Invalid character. Got `%c`, expected `%c`"
					,ch_bad,ch_good);
				message.data[511]=0;
				throw message;
				}

			static void syntaxError(const char* description)
				{
				ErrorMessage message;
				snprintf(message.data,512,"%s",description);
				message.data[511]=0;
				throw message;
				}


			template<class T>
			static std::enable_if_t<std::is_unsigned<T>::value> rangeError(T x,long long int min,long long int max)
				{
				ErrorMessage message;
				auto v=static_cast<unsigned long long int>(x);
				snprintf(message.data,512,"%llu is outside valid range. The allowed range is [%lld, %lld]"
					,v,min,max);
				message.data[511]=0;
				throw message;
				}

			template<class T>
			static std::enable_if_t<std::is_signed<T>::value> rangeError(T x,long long int min,long long int max)
				{
				ErrorMessage message;
				auto v=static_cast<long long int>(x);
				snprintf(message.data,512,"%lld is outside valid range. The allowed range is [%lld, %lld]"
					,v,min,max);
				message.data[511]=0;
				throw message;
				}

			template<class T>
			static std::enable_if_t<std::is_unsigned<T>::value> rangeError(T min,T max)
				{
				ErrorMessage message;
				auto v_min=static_cast<unsigned long long int>(min);
				auto v_max=static_cast<unsigned long long int>(max);
				snprintf(message.data,512,"Value is outside valid range. The allowed range is [%llu, %llu]"
					,v_min,v_max);
				message.data[511]=0;
				throw message;
				}

			template<class T>
			static std::enable_if_t<std::is_signed<T>::value> rangeError(T min,T max)
				{
				ErrorMessage message;
				auto v_min=static_cast<long long int>(min);
				auto v_max=static_cast<long long int>(max);
				snprintf(message.data,512,"Value outside valid range. The allowed range is [%lld, %lld]"
					,v_min,v_max);
				message.data[511]=0;
				throw message;
				}
		};
	}
#endif
