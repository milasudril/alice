//@	{"targets":[{"name":"array.hpp","type":"include"}]}

#ifndef ALICE_ARRAY_HPP
#define ALICE_ARRAY_HPP

namespace Alice
	{
	template<class T,size_t N>
	struct Array
		{
		T data[N];
		static constexpr size_t size() noexcept
			{return N;}
		};

    template <typename T, std::size_t N>
    constexpr std::size_t countof(T const (&)[N]) noexcept
		{return N;}
	}

#endif
