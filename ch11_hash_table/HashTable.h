//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/16.
//

#ifndef ITA_HASHTABLE_H
#define ITA_HASHTABLE_H

#include <vector>
#include <list>
#include <algorithm>
#include <HashFun.h>

template<typename HashFun>
class HashTable{
public:
    explicit HashTable(HashFun hasher=&hashFun_mod,std::size_t sz=101)
            :currentSize(0),SChains(101),hf(hasher){}

    bool insert(const std::string&);
    bool insert(std::string&&);
    bool search(const std::string&);
    bool remove(const std::string&);
    bool is_Empty();
    void makeEmpty();
private:
    std::vector<std::list<std::string>> SChains; //separate Chaining
    std::size_t currentSize;
    HashFun hf;

    void rehash();
};
#endif //ITA_HASHTABLE_H
