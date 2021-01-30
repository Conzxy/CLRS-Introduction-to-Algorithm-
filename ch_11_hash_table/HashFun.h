//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/16.
//

#ifndef ITA_HASHFUN_H
#define ITA_HASHFUN_H
#include <cmath>
#include <string>

/*template<unsigned p,unsigned d>
struct Is_Prime_{
    static constexpr bool value=(p%d!=0)&& Is_Prime_<p,d-1>::value;
};

template<unsigned p>
struct Is_Prime_<p,2>{
    static constexpr bool value=(p%2!=0);
};


template<unsigned p>
inline constexpr bool is_Prime=Is_Prime_<p,p/2>::value;

//to avoid endless recursion with template instantiation
//Since {0,1,2,3}/2={0,0,1,1}<2
template<>
inline constexpr bool is_Prime<0> =false;

template<>
inline constexpr bool is_Prime<1> =false;

template<>
inline constexpr bool is_Prime<2> =true;

template<>
inline constexpr bool is_Prime<3> =true;
*/

constexpr bool
Is_Prime_(unsigned p,unsigned d){
    return d!=2 ? Is_Prime_(p,d-1) : (p%2!=0);
}

constexpr bool
is_Prime(unsigned p){
    return p<4 ? p >= 2 : Is_Prime_(p, p / 2);
}
unsigned nextPrime(unsigned n){
    if(n%2==0)
        ++n;

    for(;!is_Prime(n);n+=2)
        ;

    return n;
}

std::size_t strToInt(std::string const& str){
    std::size_t num=0;
    for(auto ch:str)
        num=num*37+ch;
    return num;
}


std::size_t hashFun_mod(std::string const& str,std::size_t slots){
    return strToInt(str)%slots;
}

std::size_t hashFun_mul(std::string const& str,std::size_t slots){
    std::size_t A=(std::sqrt(5)-1)/2;
    return slots*((strToInt(str)*A)%1);
}

#endif //ITA_HASHFUN_H
