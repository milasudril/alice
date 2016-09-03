//@	{"targets":[{"name":"test2","type":"application"}]}

#include "optionmap.hpp"

struct OptionDescriptor
	{
	static constexpr const char* keys[]={"help","do-stuff-a"};
	static constexpr size_t N_options=2;
	};

template<class T,size_t N>
struct Array
	{
	T data[N];
	static constexpr size_t size() noexcept
		{return N;}
	};

template<class OptionDescriptor>
constexpr Array<Alice::Stringkey,OptionDescriptor::N_options> make_keys()
	{
	Array<Alice::Stringkey,OptionDescriptor::N_options> ret{};
	for(decltype(ret.size()) k=0;k<ret.size();++k)
		{ret.data[k]=Alice::Stringkey(OptionDescriptor::keys[k]);}
	return ret;
	}

constexpr auto keys=make_keys<OptionDescriptor>();

template<Alice::Stringkey::HashValue key,size_t N=keys.size(),bool found=false>
struct Find
	{
	static constexpr size_t index=Find<key,N-1,keys.data[N-1]==key>::index;
	typedef typename Find<key,N-1,keys.data[N-1]==key>::IndexType IndexType;
	};

template<Alice::Stringkey::HashValue key>
struct Find<key,0,false>
	{
	typedef void IndexType;
	};

template<Alice::Stringkey::HashValue key,size_t N>
struct Find<key,N,true>
	{
	static constexpr size_t index=N;
	typedef size_t IndexType;
	};

template<Alice::Stringkey::HashValue key>
typename Find<key>::IndexType find()
	{return Find<key>::index;}


int main()
	{
//	auto i=Find<Alice::Stringkey("helpw")>::index;
//	static_assert(i)
	auto i=find<Alice::Stringkey("heflp")>();
	return 0;
	}
