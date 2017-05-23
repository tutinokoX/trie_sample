//
// Created by ydoi-mac on 2017/05/20.
//

#ifndef TRIE_SAMPLE_LISTTRIE_T_HPP
#define TRIE_SAMPLE_LISTTRIE_T_HPP

#include "ListTrieBuilder.hpp"

namespace list_trie {

    class ListTrie : public ListTrieBuilder{

    public:
        bool IsTerm(){ return false; }
        char OutEndChar(){ return END_CHAR; }
        refer OutRoot() { return ROOT; }
        refer OutFree() { return nullptr; }

        bool EndCheck(refer state);
        bool NextCheck(refer next);

        refer Goto(refer state , uint8_t label);
        bool Follow(std::string key);

    };


    // 終端確認
    bool ListTrie::EndCheck(refer state) {

        // 終端確認の正しい方法がわからない・・・ （現状エラーは出てない）
        if(state->child == TERM){
            return true;
        }
        return false;
    }


    // 遷移処理の確認（ダンプテスト用）
    // 遷移処理を失敗した際に出力するエラー値は、refer（要素型）がトライによって異なるため
    bool ListTrie::NextCheck(refer next) {

        if(next != nullptr){
            return true;
        }
        return false;
    }


    // 遷移処理（子ノードへの移動）
    refer ListTrie::Goto(refer state, uint8_t label) {

        refer ptr = state->child;
        while(1){

            if(ptr->label == label) return ptr;
            if(ptr->sib == nullptr) break;
            ptr = ptr->sib;
        }

        return nullptr;
    }


    // 文字列（引数）の探索
    bool ListTrie::Follow(std::string key) {

        key += OutEndChar();
        refer ptr = ROOT;

        for(size_t i = 0 ; i < key.size() ; i++){

            ptr = Goto(ptr , static_cast<uint8_t>(key[i]));
            if(ptr == nullptr) return false;
        }

        return EndCheck(ptr);
    }


}
#endif //TRIE_SAMPLE_LISTTRIE_T_HPP
