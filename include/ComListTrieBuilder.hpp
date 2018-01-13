//
// Created by ydoi-mac on 2017/05/16.
//

#ifndef TRIE_SAMPLE_COM_LISTTRIEBUILDER_HPP
#define TRIE_SAMPLE_COM_LISTTRIEBUILDER_HPP

namespace com_list_trie{


    using refer = int;


    class ComListTrieBuilder{

    private:
        refer AddNode(uint8_t label);
        refer current_point = 0;


    protected:

        std::vector<refer> F_CHILD;
        std::vector<refer> N_SIBLING;
        std::vector<uint8_t> LABEL;

        const char END_CHAR = '#';
        refer ROOT = 0;
        refer TERM = -1;
        refer FREE = 0;

    public:

        ComListTrieBuilder(){
            F_CHILD.push_back(FREE);
            N_SIBLING.push_back(FREE);
            LABEL.push_back(1);
            current_point ++;
        }
        ~ComListTrieBuilder(){}

        bool StaticInsert(std::vector<std::string> keyset);
        bool DynamicInsert(std::string str);
    };


    refer ComListTrieBuilder::AddNode(uint8_t label) {

        // refer back_data = static_cast<refer>(F_CHILD.size());

        F_CHILD.push_back( FREE );
        N_SIBLING.push_back( FREE );
        LABEL.push_back( label );

        return current_point++;
    }

    bool ComListTrieBuilder::DynamicInsert(std::string str) {

        str += END_CHAR;
        refer inserter = ROOT;

        for(size_t i = 0 ; i < str.size() ; i++ ){

            unsigned char label_uc = static_cast<unsigned char>(str[i]);
            uint8_t label = static_cast<uint8_t>(label_uc);

            if( F_CHILD[inserter] == FREE ){
                F_CHILD[ inserter ] = AddNode( label );
            }
            inserter = F_CHILD[inserter];

            while(1){

                if( LABEL[inserter] ==  label ) break;
                if( N_SIBLING[inserter] == FREE ){
                    N_SIBLING[inserter] = AddNode( label );
                    inserter = N_SIBLING[inserter];
                    break;
                }
                inserter = N_SIBLING[inserter];
            }
        }
        F_CHILD[inserter] = TERM;

        return true;
    }


    // 仮設計
    bool ComListTrieBuilder::StaticInsert(std::vector<std::string> keyset) {

        for(size_t i = 0 ; i < keyset.size() ; i++){

            if( !DynamicInsert( keyset[i] ) ) return false;
        }

        std::cout << "F_CHILD size : " << F_CHILD.size() << "\n";

        return true;
    }


}

#endif //TRIE_SAMPLE_LISTTRIE_HPP
