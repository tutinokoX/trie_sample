//
// Created by ydoi-mac on 2017/05/16.
//

#ifndef TRIE_SAMPLE_TABLETRIE_BUILDER_HPP
#define TRIE_SAMPLE_TABLETRIE_BUILDER_HPP

#include <vector>
#include "Basics.hpp"

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

        double SizeCalc();
        void Dicsave(std::string file_path);
        void Dicload(std::string file_path);
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




    double TableTrieBuilder::SizeCalc() {
        // MByteで出力
        size_t table_size = size_vector(table);
        return (table_size) / (1024.0 * 1024.0);
    }


    void TableTrieBuilder::Dicsave(std::string file_path) {

        std::ofstream ofs(file_path);
        if (!ofs) {
            std::cerr << "DaTrieBuilder::DicSave\n";
            std::cerr << "\nopen error : " << file_path << std::endl;
            exit(1);
        }


        size_t table_num = table.size();
        write_value(table_num , ofs);
        for(int ti = 0 ; ti < table_num ; ti++){
            write_vector(table[ti] , ofs);
        }

        // show_size("\nsize (MByte) : " , SizeCalc() , std::cout);
    }

    void TableTrieBuilder::Dicload(std::string file_path) {

        std::ifstream ifs{file_path};
        if (!ifs) {
            std::cerr << "DaTrieBuilder::Dicload\n";
            std::cerr << "open error : " << file_path << std::endl;
            exit(1);
        }

        size_t table_num = 0;
        read_value(table_num , ifs);
        table.resize(table_num);
        for(int ti = 0 ; ti < table_num ; ti++){
            read_vector(table[ti] , ifs);
        }


    }


}

#endif //TRIE_SAMPLE_LISTTRIE_HPP
