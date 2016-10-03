//@ {"targets":[{"name":"optionmap.hpp","type":"include"}]}

#ifndef ALICE_OPTIONMAP_HPP
#define ALICE_OPTIONMAP_HPP

#include "typeinfo.hpp"
#include "option.hpp"
#include "array.hpp"

#include <cstddef>
#include <vector>

namespace Alice
	{
	template<class OptionDescriptor>
	class OptionMap
		{
		public:
			template<Stringkey::HashValue key>
			const auto& get() const noexcept
				{return get< Find<key>::index >(m_data);}

			template<Stringkey::HashValue key>
			auto& get() noexcept
				{return get< Find<key>::index >(m_data);}

			template<size_t index>
			const auto& getByIndex() const noexcept
				{return get<index>(m_data);}

			template<size_t index>
			auto& getByIndex() noexcept
				{return get<index>(m_data);}

			static constexpr size_t size() noexcept
				{return s_keys.size();}

			template<class Callback>
			void itemsEnum(Callback&& cb) const
				{itemsEnumImpl(cb);}

			template<class Callback>
			void itemsEnum(Callback&& cb)
				{itemsEnumImpl(cb);}

			static const Stringkey* keysBegin() noexcept
				{return s_keys.data;}

			static const Stringkey* keysEnd() noexcept
				{return s_keys.data + size();}


		private:
			static constexpr Array<Stringkey,countof(OptionDescriptor::options)> make_keys()
				{
				Array<Stringkey,countof(OptionDescriptor::options)> ret{};
				for(decltype(ret.size()) k=0;k<ret.size();++k)
					{ret.data[k]=Alice::Stringkey(OptionDescriptor::options[k].nameGet());}
				return ret;
				}

			static constexpr Array<Stringkey,countof(OptionDescriptor::options)> s_keys=make_keys();

			template<class T,Option::Multiplicity multiplicity>
			struct MultiplicitySelector
				{};

			template<class T>
			struct MultiplicitySelector<T,Option::Multiplicity::ONE>
				{
				typedef T Type;
				static constexpr bool multi=0;
				};

			template<class T>
			struct MultiplicitySelector<T,Option::Multiplicity::ZERO_OR_MORE>
				{
				typedef std::vector<T> Type;
				static constexpr bool multi=1;
				};

			template<class T>
			struct MultiplicitySelector<T,Option::Multiplicity::ONE_OR_MORE>:
				public MultiplicitySelector<T,Option::Multiplicity::ZERO_OR_MORE>
				{};

			template<class T>
			struct MultiplicitySelector<T,Option::Multiplicity::ZERO_OR_ONE>:
				public MultiplicitySelector<T,Option::Multiplicity::ZERO_OR_MORE>
				{};

			template<size_t k=countof(OptionDescriptor::options),bool dummy=true>
			struct Content:public Content<k-1>
				{
				public:
					Content()=default;

					static constexpr Stringkey element_type{OptionDescriptor::options[k - 1].typeGet()};
					static constexpr auto multiplicity=OptionDescriptor::options[k-1].multiplicityGet();

					typedef typename MultiplicitySelector<
						 typename MakeType<element_type>::Type
						,multiplicity>::Type ValueType;

					static constexpr bool multi=MultiplicitySelector<
						 typename MakeType<element_type>::Type
						,multiplicity>::multi;

					const ValueType& valueGet() const noexcept
						{return m_data.first;}

					void valueSet(ValueType&& value) noexcept
						{
						m_data.first=std::move(value);
						m_data.second=1;
						}	

					operator bool() const noexcept
						{return m_data.second;}

				private:
					Content(const Content&)=delete;
					std::pair<ValueType,bool> m_data;
				};

			template<bool dummy>
			struct Content<0,dummy>
				{};

			Content<countof(OptionDescriptor::options)> m_data;

			template<size_t k>
			const auto& get(const Content<k+1>& vals) const noexcept
				{return vals;}

			template<size_t k>
			auto& get(Content<k+1>& vals) noexcept
				{return vals;}

			template<Stringkey::HashValue key,size_t N=s_keys.size(),bool found=false>
			struct Find
				{
				static constexpr size_t index=Find<key,N-1,s_keys.data[N-1]==key>::index;
				typedef typename Find<key,N-1,s_keys.data[N-1]==key>::IndexType IndexType;
				};

			template<Stringkey::HashValue key>
			struct Find<key,0,false>
				{
				typedef void IndexType;
				};

			template<Stringkey::HashValue key,size_t N>
			struct Find<key,N,true>
				{
				static constexpr size_t index=N;
				typedef size_t IndexType;
				};

			template<size_t index=0,class Callback>
			typename std::enable_if<index!=size(),void>::type
			itemsEnumImpl(Callback& cb)
				{
				cb(index,s_keys.data[index],getByIndex<index>());
				itemsEnumImpl<index+1,Callback>(cb);
				}

			template<size_t index=0,class Callback>
			typename std::enable_if<index!=size(),void>::type
			itemsEnumImpl(Callback& cb) const
				{
				cb(index,s_keys.data[index],getByIndex<index>());
				itemsEnumImpl<index+1,Callback>(cb);
				}


			template<size_t index,class Callback>
			typename std::enable_if<index==size(),void>::type
			itemsEnumImpl(Callback& cb) const noexcept
				{}	
		};

	template<class OptionDescriptor>
	constexpr const Array<Stringkey,countof(OptionDescriptor::options)> OptionMap<OptionDescriptor>::s_keys;
	}

#endif
