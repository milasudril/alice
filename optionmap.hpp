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

			static constexpr size_t size() noexcept
				{return sizeof...(entries);}

			template<class Callback>
			void itemsEnum(Callback&& cb) const
				{itemsEnumImpl(cb);}

			template<class Callback>
			void itemsEnum(Callback&& cb)
				{itemsEnumImpl(cb);}

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

			template<size_t index=0,class Callback>
			typename std::enable_if<index!=sizeof...(entries),void>::type
			itemsEnumImpl(Callback& cb)
				{
				cb(getByIndex<index>(),index,s_keys[index]);
				itemsEnumImpl<index+1,Callback>(cb);
				}

			template<size_t index=0,class Callback>
			typename std::enable_if<index!=sizeof...(entries),void>::type
			itemsEnumImpl(Callback& cb) const
				{
				cb(getByIndex<index>(),index,s_keys[index]);
				itemsEnumImpl<index+1,Callback>(cb);
				}


			template<size_t index,class Callback>
			typename std::enable_if<index==sizeof...(entries),void>::type
			itemsEnumImpl(Callback& cb) const noexcept
				{}	
		};

	template<class KeyType,class ... entries>
	constexpr KeyType OptionMapImpl<KeyType,entries...>::s_keys[sizeof...(entries)];

	template<class ... entries>
	using OptionMap=OptionMapImpl<Stringkey::HashValue,entries...>;

	template<Stringkey::HashValue key,class OptionType>
	using OptionMapEntry=OptionMapEntryImpl<Stringkey::HashValue,key,OptionType>;
	}

#endif
