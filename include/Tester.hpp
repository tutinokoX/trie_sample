//
// Created by ydoi-mac on 2017/05/09.
//
// trieに必要な関数
//   - EndCheck
//   - Goto
//   - OutEndChar
//   - Find
//

#ifndef XSDA_DEV_TESTER_HPP
#define XSDA_DEV_TESTER_HPP

#include <iostream>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <utility>
#include <vector>
#include "ProcessTimer.hpp"
#include "StateOut.hpp"



class RandomNumberGenerator
{
public:
    std::ptrdiff_t operator()(std::ptrdiff_t limit) const
    {
        return ((std::rand() * (static_cast<std::ptrdiff_t>(RAND_MAX) + 1))
                + std::rand()) % limit;
    }
};


class Tester{

private:
    std::vector<std::string> _KEYSET;
    std::vector<std::string> _RANDOM_KEYSET;

    // 内部関数
    void randomize_keys(const std::vector<std::string> &keys, std::vector<std::string> *random_keys);
    void read_keys(std::string file_path, std::vector<std::string> &keys);


public:

    Tester(){}
    ~Tester(){}

    void set_keys( std::string filepath );


    template <class T>
    bool find_speed_test( T& trie );

    template <class T>
    bool find_test( T& trie );

    template <class T>
    bool dump_test( T& trie );

};


void Tester::randomize_keys(const std::vector<std::string> &keys,
                            std::vector<std::string> *random_keys)
{
    *random_keys = keys;

    RandomNumberGenerator gen;
    std::random_shuffle(random_keys->begin(), random_keys->end(), gen);
}


void Tester::read_keys(std::string file_path, std::vector<std::string> &KEYSET) {

    std::ifstream ifs(file_path);
    if (ifs.fail()) {
        std::cerr << " read_keys " << std::endl;
        std::cerr << " err : file open -> " << file_path << std::endl;
        exit(1);
    }
    std::string key;
    while (getline(ifs, key)) KEYSET.push_back(key);
    sort(KEYSET.begin(), KEYSET.end());
    KEYSET.erase(unique(KEYSET.begin(), KEYSET.end()), KEYSET.end());
}


void Tester::set_keys(std::string filepath) {

    std::cout << "read_kyset ... " << std::flush;
    read_keys(filepath, _KEYSET);
    std::cout << "done.\n";


    std::cout << "random_kyset ... " << std::flush;
    randomize_keys(_KEYSET, &_RANDOM_KEYSET);
    std::cout << "done.\n";

}



template <class T>
struct refer_select;

template <>
struct refer_select< list_trie::ListTrie > { using type = list_trie::refer; };

// template <>
// struct refer_select< table_trie::TableTrie >{ using type = table_trie::refer; };


template <class T>
bool Tester::find_speed_test( T &trie ){

    using Refer = typename refer_select<T>::type;

    if(_RANDOM_KEYSET.empty()){
        std::cerr << "err : KEYSETが設定されていません\n";
        return false;
    }

    std::cout << "find_speed_test ... " << std::endl;

    ProcessTimer pt;
    pt.AddTimerSuffix(0 , 1);
    pt.StartTimer();

    for(size_t i = 0 ; i < _RANDOM_KEYSET.size() ; i++) {

        std::string key = _RANDOM_KEYSET[i];
        Refer ptr = trie.OutRoot();

        for(size_t j = 0 ; j < key.size() ; j++){

            ptr = trie.Goto( ptr , static_cast<uint8_t>(key[j]) );
            if(ptr == trie.OutFree()){
                std::cerr << "err 　" << i << " : " << _RANDOM_KEYSET[i] << "\n";
                // return false;
            }
        }

    }

    pt.Measure(0);
    pt.Output();

    std::cout << "done.\n";

    return true;
}




template <class T>
bool Tester::find_test( T &trie ) {

    using Refer = typename refer_select<T>::type;


    std::cout << "find_test ... " << std::endl;
    for (size_t i = 0; i < _RANDOM_KEYSET.size(); i++) {

        std::string key = _RANDOM_KEYSET[i];

        // ここで、終端まで探索していないのは間違えてる気がする。
        // 他の実装を確認
        if (!trie.Follow( key )) {
            std::cerr << "err 　" << i << " : " << _RANDOM_KEYSET[i] << "\n";
            return false;
        }

    }

    std::cout << "done.\n";

    return true;
}




template <class T>
bool Tester::dump_test( T &trie ) {

    using Refer = typename refer_select<T>::type;

    std::cout << "dump_test ... " << std::endl;
    Refer current = trie.OutRoot();
    std::queue<Refer> goto_list;
    goto_list.push(current);
    uint64_t dump_count = 0;

    StateOut so;
    so.AddMaxState( _KEYSET.size() );
    so.StartSet();

    while (1) {

        if ( goto_list.empty() ) break;
        current = goto_list.front();
        goto_list.pop();

        if( trie.EndCheck( current ) ){
            dump_count ++;
            so.Output( dump_count );
            if( !trie.IsTerm() ) continue;   // 終端フラグならこの処理は必要なし : 動的に変更するように検討
        }

        for (int l = 0; l <= 255; l++) {
            Refer next = trie.Goto( current , static_cast<uint8_t >(l) );
            if (trie.NextCheck( next )) {
                goto_list.push( next );
            }
        }

    }
    std::cout << "\ndump_count : " << dump_count << "\n";
    std::cout << "done.\n";

    return true;
}

#endif //XSDA_DEV_TESTER_HPP
