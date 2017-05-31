//
// Created by ydoi-mac on 2017/05/22.
//

#ifndef TRIE_SAMPLE_DATRIE_HPP
#define TRIE_SAMPLE_DATRIE_HPP

#include "DaTrieBuilder.hpp"


namespace da_trie{

    class DaTrie : public DaTrieBuilder{


    public:
        bool IsTerm(){ return false; }
        char OutEndChar(){ return END_CHAR; }
        refer OutRoot() { return ROOT; }
        refer OutFree() { return FREE; }

        bool EndCheck(refer state);
        bool NextCheck(refer next);

        refer Goto(refer state , uint8_t label);
        bool Follow(std::string key);
    };


    refer DaTrie::Goto(refer state, uint8_t label) {

        refer next = BASE[ static_cast<size_t>(state) ] + label;
        if(state != CHECK[ static_cast<size_t >(next) ])
            return FREE;

        return next;
    }


    bool DaTrie::Follow(std::string key) {

        refer state = ROOT;
        for(size_t i = 0 ; i < key.size() ; i++){
            // unsigned char label_uc = static_cast<unsigned char>(key[i]);
            uint8_t label = static_cast< uint8_t >(key[i]);

            state = Goto(state , label);
            if(state == FREE) return false;
        }

        return true;
    }


    bool DaTrie::EndCheck(refer state) {

        if(BASE[static_cast<size_t >(state)] == TERM)
            return true;

        return false;
    }


    bool DaTrie::NextCheck(refer next) {

        if(next != FREE)
            return true;

        return false;
    }

}

#endif //TRIE_SAMPLE_DATRIE_HPP
