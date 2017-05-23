//
// Created by ydoi-mac on 2017/05/22.
//

#ifndef TRIE_SAMPLE_DATRIE_HPP
#define TRIE_SAMPLE_DATRIE_HPP

#include "DaTrieBuilder.hpp"


namespace da_trie{

    class DaTrie : public DaTrieBuilder{


        refer Goto(refer state , uint8_t label);
        bool Follow(std::string key);
    };

}

#endif //TRIE_SAMPLE_DATRIE_HPP
