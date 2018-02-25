//
// Created by ydoi-mac on 2017/05/16.
//

#ifndef TRIE_SAMPLE_LISTTRIEBUILDER_HPP
#define TRIE_SAMPLE_LISTTRIEBUILDER_HPP

namespace list_trie{

    struct node{
        node *child;
        node *sib;
        uint8_t label;
        node(uint8_t _label = 0){
            child = nullptr;
            sib = nullptr;
            label = _label;
        }
    };

    using refer = node*;


    class ListTrieBuilder{

    protected:
        const char END_CHAR = '#';
        refer ROOT = new node;
        refer TERM = nullptr;
        refer FREE = nullptr;

    public:

        ListTrieBuilder(){}
        ~ListTrieBuilder(){}

        bool StaticInsert(std::vector<std::string> keyset);
        bool DynamicInsert(std::string str);
    };



    bool ListTrieBuilder::DynamicInsert(std::string str) {

        str += END_CHAR;
        refer inserter = ROOT;

        for(size_t i = 0 ; i < str.size() ; i++ ){

            unsigned char label_uc = static_cast<unsigned char>(str[i]);
            uint8_t label = static_cast<uint8_t>(label_uc);

            if( inserter->child == nullptr ){
                inserter->child = new node( label );
            }
            inserter = inserter->child;

            while(1){

                if( inserter->label ==  label ) break;
                if( inserter->sib == nullptr ){
                    inserter->sib = new node( label );
                    inserter = inserter->sib;
                    break;
                }
                inserter = inserter->sib;
            }
        }

        return true;
    }

    // 仮設計
    bool ListTrieBuilder::StaticInsert(std::vector<std::string> keyset) {

        for(size_t i = 0 ; i < keyset.size() ; i++){

            if( !DynamicInsert( keyset[i] ) ) return false;
        }

        return true;
    }
    
}

#endif //TRIE_SAMPLE_LISTTRIE_HPP
