//@	{"targets":[{"name":"array.hpp","type":"include"}]}

#ifndef ALICE_ARRAY_HPP
#define ALICE_ARRAY_HPP

#include <cstddef>

namespace Alice
	{
	template<class T,size_t N>
	struct Array
		{
		T data[N];
		static constexpr size_t size() noexcept
			{return N;}

		constexpr Array<T,N+1> append(const T& obj) const noexcept
			{
			Array<T,N+1> ret{};
			for(size_t k=0;k<N;++k)
				{ret.data[k]=data[k];}
			ret.data[N]=obj;
			return ret;
			}

		template<size_t M>
		constexpr Array<T,N+M> append(const Array<T,M>& array) const noexcept
			{
			Array<T,N+M> ret{};
			for(size_t k=0;k<N;++k)
				{ret.data[k]=data[k];}
			for(size_t k=0;k<M;++k)
				{ret.data[k+N]=array.data[k];}
			return ret;
			}
		};

    template<class T, size_t N>
    constexpr size_t countof(T const (&)[N]) noexcept
		{return N;}

	template<class T, size_t N>
	constexpr Array<T,N + 1> append(const Array<T,N>& array,const T& obj)
		{return array.append(obj);}

	template<class T, size_t N>
	constexpr Array<T,N + 1> append(const T& obj,const Array<T,N>& array)
		{
		Array<T,N+1> ret{obj};
		for(size_t k=0;k<N;++k)
			{ret.data[k+1]=array.data[k];}
		return ret;
		}

	constexpr size_t static_strlen(const char* str)
		{
		return *str==0?0: 1 + static_strlen(str+1);
		}

	template<class StringHolder>
	constexpr auto make_array()
		{
		constexpr auto N=static_strlen(StringHolder::get());
		Array<char,N> ret{};
		auto str=StringHolder::get();
		for(size_t k=0;k<N;++k)
			{ret.data[k]=*(str+k);}
		return ret;
		}
	}

#endif
