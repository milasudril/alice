//@ {"targets":[{"name":"optionmap2.hpp","type":"include"}]}

#ifndef ALICE_OPTIONMAP_HPP
#define ALICE_OPTIONMAP_HPP

#include "stringkey.hpp"
#include "typeinfo.hpp"

#include <cstddef>

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

		private:
			template<class T,size_t N>
			struct Array
				{
				T data[N];
				static constexpr size_t size() noexcept
					{return N;}
				};

			static constexpr Array<Stringkey,OptionDescriptor::size> make_keys()
				{
				Array<Stringkey,OptionDescriptor::size> ret{};
				for(decltype(ret.size()) k=0;k<ret.size();++k)
					{ret.data[k]=Alice::Stringkey(OptionDescriptor::options[k].nameGet());}
				return ret;
				}

			static constexpr Array<Stringkey,OptionDescriptor::size> s_keys=make_keys();

			template<size_t k=OptionDescriptor::size,bool dummy=true>
			struct Content:public Content<k-1>
				{
				typename MakeType<Stringkey(OptionDescriptor::options[k-1].typeGet())>::Type value;
				};

			template<bool dummy>
			struct Content<0,dummy>
				{};

			Content<OptionDescriptor::size> m_data;

			template<size_t k>
			const auto& get(const Content<k+1>& vals) noexcept
				{return vals.value;}

			template<size_t k>
			auto& get(Content<k+1>& vals) noexcept
				{return vals.value;}

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
		};


	}

#endif