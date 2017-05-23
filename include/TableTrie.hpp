//
// Created by ydoi-mac on 2017/05/20.
//

#ifndef TRIE_SAMPLE_TABLETRIE_HPP
#define TRIE_SAMPLE_TABLETRIE_HPP

#include "TableTrieBuilder.hpp"

namespace table_trie {

    class TableTrie : public TableTrieBuilder{

    private:
        uint8_t END_LABEL;

    public:
        TableTrie();

        bool IsTerm(){ return true; }
        char OutEndChar(){ return END_CHAR; }
        refer OutRoot() { return ROOT; }
        refer OutFree() { return FREE; }

        bool EndCheck(refer state);
        bool NextCheck(refer next);

        refer Goto(refer state , uint8_t label);
        bool Follow(std::string key);

    };

    TableTrie::TableTrie() {
        unsigned char label_uc = static_cast<unsigned char>(END_CHAR);
        END_LABEL = static_cast<uint8_t>(label_uc);
    }



    bool TableTrie::EndCheck(refer state) {

        if(table[state][END_LABEL] == TERM){
            return true;
        }
        return false;
    }


    bool TableTrie::NextCheck(refer next) {

        if(next == FREE || next == TERM){
            return false;
        }
        return true;
    }


    refer TableTrie::Goto(refer state , uint8_t label) {

        return table[state][label];
    }


    bool TableTrie::Follow(std::string key) {

        refer ptr = ROOT;

        for(size_t i = 0 ; i < key.size() ; i++) {

            ptr = Goto(ptr, static_cast<uint8_t>( key[i] ));
            if (ptr == FREE) return false;
        }

        return EndCheck(ptr);
    }


}
#endif //TRIE_SAMPLE_LISTTRIE_T_HPP
