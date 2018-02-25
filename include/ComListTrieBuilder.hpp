//
// Created by ydoi-mac on 2017/05/16.
//

#ifndef TRIE_SAMPLE_COM_LISTTRIEBUILDER_HPP
#define TRIE_SAMPLE_COM_LISTTRIEBUILDER_HPP

#include "Basics.hpp"

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

        double SizeCalc();
        void Dicsave(std::string file_path);
        void Dicload(std::string file_path);

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

        // std::cout << "F_CHILD size : " << F_CHILD.size() << "\n";

        return true;
    }


    double ComListTrieBuilder::SizeCalc() {

        size_t f_child_size = size_vector(F_CHILD);
        size_t n_sibling_size = size_vector(N_SIBLING);
        size_t label_size = size_vector(LABEL);

        return (f_child_size + n_sibling_size + label_size) / (1024.0 * 1024.0);
    }

    void ComListTrieBuilder::Dicsave(std::string file_path) {

        std::ofstream ofs(file_path);
        if (!ofs) {
            std::cerr << "ComListTrieBuilder::DicSave\n";
            std::cerr << "\nopen error : " << file_path << std::endl;
            exit(1);
        }

        write_vector(F_CHILD , ofs);
        write_vector(N_SIBLING , ofs);
        write_vector(LABEL , ofs);

        // show_size("\nsize (MByte) : " , SizeCalc() , std::cout);
    }


    void ComListTrieBuilder::Dicload(std::string file_path) {
        std::ifstream ifs{file_path};
        if (!ifs) {
            std::cerr << "ComListTrieBuilder::Dicload\n";
            std::cerr << "open error : " << file_path << std::endl;
            exit(1);
        }

        read_vector(F_CHILD , ifs);
        read_vector(N_SIBLING , ifs);
        read_vector(LABEL , ifs);
    }

}

#endif //TRIE_SAMPLE_LISTTRIE_HPP
