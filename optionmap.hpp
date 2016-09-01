//@	{"targets":[{"name":"optionmap.hpp","type":"include"}]}

#ifndef ALICE_OPTIONMAP_HPP
#define ALICE_OPTIONMAP_HPP

#include "optionbase.hpp"
#include "stringkey.hpp"
#include <tuple>
#include <map>
#include <cstdio>

namespace Alice
	{
	class OptionRuntime;

	template<class KeyType,KeyType key,class OptionType>
	class OptionMapEntryImpl
		{
		public:
			typedef OptionType type;
			static constexpr KeyType s_key=key;
		};

	template<class KeyType,class ... entries>
	class OptionMapImpl
		{
		public:
			template<KeyType key>
			auto get() const noexcept
				{return std::get<Find<key>::index>(m_values);}

			template<KeyType key>
			auto& get() noexcept
				{return std::get<Find<key>::index>(m_values);}

			template<size_t index>
			auto getByIndex() const noexcept
				{return std::get<index>(m_values);}

			template<size_t index>
			auto& getByIndex() noexcept
				{return std::get<index>(m_values);}

			template<size_t index=0,class Callback>
			typename std::enable_if<index!=sizeof...(entries),void>::type
			itemsEnum(Callback&& cb)
				{
				cb(getByIndex<index>());
				itemsEnum<index+1,Callback>();
				}

			template<size_t index,class Callback>
			typename std::enable_if<index==sizeof...(entries),void>::type
			itemsEnum(Callback&&) const noexcept
				{}				

			static constexpr size_t size() noexcept
				{return sizeof...(entries);}

			template<size_t index=0>
			typename std::enable_if<index!=sizeof...(entries), void>::type
			helpPrint(bool print_groups,KeyType group_prev=0) const noexcept
				{
				if(index==0)
					{
					printf("Command line options\n"
					       "====================\n");
					}
				auto x=std::get<index>(m_values);
				const auto& group_next=KeyType(x.groupGet());
				x.helpPrint(group_next!=group_prev && print_groups);
				helpPrint<index + 1>(print_groups,group_next);
				}

			template<size_t index=0>
			typename std::enable_if<index==sizeof...(entries),void>::type
			helpPrint(bool,KeyType) const noexcept
				{}

			template<size_t index=0>
			typename std::enable_if<index!=sizeof...(entries), void>::type
			valuesPrint() const noexcept
				{
				if(index==0)
					{printf("{");}
				const auto& x=std::get<index>(m_values);
				x.valuesPrint();
				if(index + 1!=sizeof...(entries))
					{printf(",");}
				valuesPrint<index + 1>();
				}

			template<size_t index=0>
			typename std::enable_if<index==sizeof...(entries),void>::type
			valuesPrint() const noexcept
				{printf("}");}



			template<size_t index=0>
			typename std::enable_if<index!=sizeof...(entries), void>::type
			valuesCollect(const std::map<KeyType,OptionRuntime>& values) noexcept
				{
				auto i=values.find(s_keys[index]);
				if(i!=values.end())
					{std::get<index>(m_values).valuesSet(i->second);}
				valuesCollect<index + 1>(values);
				}

			template<size_t index=0>
			typename std::enable_if<index==sizeof...(entries),void>::type
			valuesCollect(const std::map<KeyType,OptionRuntime>& values) const noexcept
				{}


		/*	template<size_t index=0>
			typename std::enable_if<index!=sizeof...(entries),void>::type
			entriesInit(const std::initializer_list<OptionBase>& option_info) noexcept
				{
				std::get<index>(m_values)=option_info[index];
				entriesInit<index + 1>(option_info);
				}

			template<size_t index=0>
			typename std::enable_if<index!=sizeof...(entries),void>::type
			entriesInit(const std::initializer_list<OptionBase>& option_info) const noexcept
				{}*/

			static const KeyType* keysBegin() noexcept
				{return s_keys;}

			static const KeyType* keysEnd() noexcept
				{return s_keys + sizeof...(entries);}
				

		private:
			static constexpr KeyType s_keys[sizeof...(entries)]={entries::s_key...};
			std::tuple<typename entries::type...> m_values;

			template<KeyType key,size_t k=sizeof...(entries),bool found=false>
			struct Find
				{
				static constexpr size_t index=Find<key,k-1,key==s_keys[k-1]>::index;
				};

			template<KeyType key,size_t k>
			struct Find<key,k,true>
				{
				static constexpr size_t index=k;
				};

			template<KeyType key>
			struct Find<key,0,false>
				{};
		};

	template<class KeyType,class ... entries>
	constexpr KeyType OptionMapImpl<KeyType,entries...>::s_keys[sizeof...(entries)];

	template<class ... entries>
	using OptionMap=OptionMapImpl<Stringkey::HashValue,entries...>;

	template<Stringkey::HashValue key,class OptionType>
	using OptionMapEntry=OptionMapEntryImpl<Stringkey::HashValue,key,OptionType>;
	}

#endif
