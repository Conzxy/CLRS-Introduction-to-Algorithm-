//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/16.
//

#ifndef ITA_HASNTABLE_IMPL_H
#define ITA_HASNTABLE_IMPL_H

#include <HashTable.h>

template<typename HashFun>
bool HashTable<HashFun>::insert(const std::string& val){
    auto& whichList=SChains[hf(val),SChains.size()];

    if(std::find(whichList.begin(),whichList.end(),val)!=whichList.end()){
        return false;
    }

    whichList.push_back(val);
    if(++currentSize>SChains.size())
        rehash();
    return true;
}

template<typename HashFun>
bool HashTable<HashFun>::insert(std::string&& val){
    auto& whichList=SChains[hf(val,SChains.size())];

    if(std::find(whichList.begin(),whichList.end(),val)!=whichList.end()){
        return false;
    }

    whichList.push_back(std::move(val));
    if(++currentSize>SChains.size())
        rehash();
    return true;
}

template<typename HashFun>
bool HashTable<HashFun>::search(const std::string& val){
    auto& whichList=SChains[hf(val,SChains.size())];
    return std::find(whichList.begin(),whichList.end(),val)!=whichList.end();
}

template<typename HashFun>
bool HashTable<HashFun>::remove(const std::string &val){
    auto& whichList=SChains[hf(val,SChains.size())];

    auto iter=std::find(whichList.begin(),whichList.end(),val);

    if(iter==whichList.end())
        return false;

    whichList.erase(iter);
    --currentSize;
    return true;
}

template<typename HashFun>
bool HashTable<HashFun>::is_Empty() {
    return currentSize!=0;
}

template<typename HashFun>
void HashTable<HashFun>::makeEmpty() {
    for(auto & list : SChains)
            list.clear();

    currentSize=0;
}

template<typename HashFun>
void HashTable<HashFun>::rehash() {
    auto oldSChains=SChains;

    makeEmpty();

    SChains.resize(nextPrime(2*SChains.size()));

    for(auto & list : oldSChains)
        for(auto & e :list)
            insert(std::move(e));
}

#endif //ITA_HASNTABLE_IMPL_H
