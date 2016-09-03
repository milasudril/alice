//@	{"targets":[{"name":"test2","type":"application"}]}

#include "typeinfo.hpp"
#include "optionbase.hpp"

using namespace Alice;

struct OptionDescriptor
	{
	static constexpr const OptionBase keys[]=
		{
			 {"General","help","Prints this message and exits","String",OptionBase::Multiplicity::ZERO_OR_ONE}
			,{"General","a-number","A number","Double",OptionBase::Multiplicity::ZERO_OR_ONE}
		};
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
constexpr Array<Stringkey,OptionDescriptor::N_options> make_keys()
	{
	Array<Stringkey,OptionDescriptor::N_options> ret{};
	for(decltype(ret.size()) k=0;k<ret.size();++k)
		{ret.data[k]=Alice::Stringkey(OptionDescriptor::keys[k].nameGet());}
	return ret;
	}

constexpr auto keys=make_keys<OptionDescriptor>();

template<size_t k=OptionDescriptor::N_options>
struct Values:public Values<k-1>
	{
	typename MakeType<Stringkey(OptionDescriptor::keys[k-1].typeGet())>::Type value;
	};

template<>
struct Values<0>
	{};

template<size_t k>
const auto& get(const Values<k+1>& vals) noexcept
	{return vals.value;}

template<size_t k>
auto& get(Values<k+1>& vals) noexcept
	{return vals.value;}



template<Stringkey::HashValue key,size_t N=keys.size(),bool found=false>
struct Find
	{
	static constexpr size_t index=Find<key,N-1,keys.data[N-1]==key>::index;
	typedef typename Find<key,N-1,keys.data[N-1]==key>::IndexType IndexType;
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

template<Stringkey::HashValue key>
typename Find<key>::IndexType find()
	{return Find<key>::index;}


int main()
	{
	Values<2> foo;
	auto i=find<Stringkey("help")>();

	get<0>(foo)="Hello";
	get<1>(foo)=1.2;

	return 0;
	}
