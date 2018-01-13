//
// Created by ydoi-mac on 2017/05/20.
//

#ifndef TRIE_SAMPLE_LISTTRIE_T_HPP
#define TRIE_SAMPLE_LISTTRIE_T_HPP

#include "ComListTrieBuilder.hpp"

namespace com_list_trie {

    class ComListTrie : public ComListTrieBuilder{

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


    // 終端確認
    bool ComListTrie::EndCheck(refer state) {

        // 終端確認の正しい方法がわからない・・・ （現状エラーは出てない）
        if( F_CHILD[state]  == TERM ){
            return true;
        }
        return false;
    }


    // 遷移処理の確認（ダンプテスト用）
    // 遷移処理を失敗した際に出力するエラー値は、refer（要素型）がトライによって異なるため
    bool ComListTrie::NextCheck(refer next) {

        if(next != FREE){
            return true;
        }
        return false;
    }


    // 遷移処理（子ノードへの移動）
    refer ComListTrie::Goto(refer state, uint8_t label) {

        refer ptr = F_CHILD[state];
        while(1){

            if(LABEL[ptr] == label) return ptr;
            if(N_SIBLING[ptr] == FREE) break;
            ptr = N_SIBLING[ptr];
        }

        return FREE;
    }


    // 文字列（引数）の探索
    bool ComListTrie::Follow(std::string key) {

        key += OutEndChar();
        refer ptr = ROOT;

        for(size_t i = 0 ; i < key.size() ; i++){

            ptr = Goto(ptr , static_cast<uint8_t>(key[i]));
            if(ptr == FREE) return false;
        }

        return EndCheck(ptr);
    }


}
#endif //TRIE_SAMPLE_LISTTRIE_T_HPP
