/*
 * main.cpp
 * */

#include <gtest/gtest.h>
#include "TableTrie.hpp"
#include "ComListTrie.hpp"
#include "ListTrie.hpp"
#include "DaTrie.hpp"
#include "Tester.hpp"
#include "TrieUtility.hpp"

// using namespace list_trie;
// using namespace table_trie;

namespace {

    Tester tester;
    TrieUtility tu;

    std::string da_size;
    std::string list_size;
    std::string table_size;


    std::string da_speed;
    std::string list_speed;
    std::string table_speed;

    list_trie::ListTrie trie;

}

TEST(Trie , build){

    std::string file_path = "../test/_keyset/wordnet-3.0-word-100000";
    tester.set_keys(file_path);
    tu.SetKeys(file_path);
    
    std::cout << "keyset : wordnet" << std::endl;
}



TEST(triebuild , da ) {

    da_trie::DaTrie trie;
    tu.SetSavepath("../test/_savedic/wordnet_da.dic");
    tu.Build(trie);
    tu.Save(trie);
    da_size = tu.SizeCalc(trie);
}

TEST(triebuild , list ) {

    com_list_trie::ComListTrie trie;
    tu.SetSavepath("../test/_savedic/wordnet_list.dic");
    tu.Build(trie);
    tu.Save(trie);
    list_size = tu.SizeCalc(trie);
}

TEST(triebuild , table ) {

    table_trie::TableTrie trie;
    tu.SetSavepath("../test/_savedic/wordnet_table.dic");
    tu.Build(trie);
    tu.Save(trie);
    table_size = tu.SizeCalc(trie);
}



TEST(findspeed , da ) {

    da_trie::DaTrie trie;
    tu.Load(trie , "../test/_savedic/wordnet_da.dic");
    da_speed = tester.find_speed_test_out(trie);
}

TEST(findspeed , list ) {

    com_list_trie::ComListTrie trie;
    tu.Load(trie , "../test/_savedic/wordnet_list.dic");
    list_speed = tester.find_speed_test_out(trie);
}

TEST(findspeed , table ) {

    table_trie::TableTrie trie;
    tu.Load(trie , "../test/_savedic/wordnet_table.dic");
    table_speed = tester.find_speed_test_out(trie);
}


TEST(result , all){

    std::cout << "********************************" << std::endl;
    std::cout << " name " << "\t|" << " size            " << "\t|" << " speed " << std::endl;
    std::cout << "table " << "\t|" << table_size << "\t|" << table_speed << std::endl;
    std::cout << "clist " << "\t|" << list_size << "\t|" << list_speed << std::endl;
    std::cout << "da    " << "\t|" << da_size << "\t|" << da_speed << std::endl;
    std::cout << "********************************" << std::endl;

}