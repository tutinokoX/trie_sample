//
// Created by ydoi-mac on 2017/05/16.
//

#ifndef TRIE_SAMPLE_TABLETRIE_BUILDER_HPP
#define TRIE_SAMPLE_TABLETRIE_BUILDER_HPP

#include <vector>


namespace table_trie{

    using refer = int;


    class TableTrieBuilder{

    protected:

        const char END_CHAR = '#';
        refer ROOT = 0;
        refer FREE = 0;
        refer TERM = -1;
        std::vector<refer> null_array;
        std::vector< std::vector<refer> > table;

    public:

        TableTrieBuilder();
        ~TableTrieBuilder(){}

        bool StaticInsert(std::vector<std::string> keyset);
        bool DynamicInsert(std::string str);
    };


    TableTrieBuilder::TableTrieBuilder() {

        null_array.resize(256 , FREE);
        table.push_back(null_array);
    }


    bool TableTrieBuilder::DynamicInsert(std::string str) {

        refer inserter = ROOT;
        unsigned char label_uc;
        uint8_t label;

        for(size_t i = 0 ; i < str.size() ; i++ ) {

            label_uc = static_cast<unsigned char>(str[i]);
            label = static_cast<uint8_t>(label_uc);

            if (label == 0) {

                std::cerr << "error : key = 0 ..\n";
                return false;
            }

            if (table[inserter][label] == 0) {

                table[inserter][label] = static_cast<refer>(table.size());
                table.push_back(null_array);
            }
            inserter = table[inserter][label];

        }

        label_uc = static_cast<unsigned char>(END_CHAR);
        label = static_cast<uint8_t>(label_uc);
        table[inserter][label] = TERM;

        return true;
    }


    // 仮設計
    bool TableTrieBuilder::StaticInsert(std::vector<std::string> keyset) {

        for(size_t i = 0 ; i < keyset.size() ; i++){

            if( !DynamicInsert( keyset[i] ) ) return false;
        }

        return true;
    }


}

#endif //TRIE_SAMPLE_LISTTRIE_HPP
