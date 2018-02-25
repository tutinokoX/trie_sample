/*
 * main.cpp
 * */

#include <gtest/gtest.h>
#include "TableTrie.hpp"
#include "Tester.hpp"
#include "TrieUtility.hpp"

// using namespace list_trie;
// using namespace table_trie;

namespace {

    Tester tester;
    TrieUtility tu;
    std::string save_path = "../test/_savedic/tabletrie.dic";
}

TEST(TableTrie , keyset){

    std::string file_path;
    std::cout << "keyset path \n ->";
    std::cin >> file_path;
    // file_path = "../../../test/keyset/wordnet-3.0-word-100000";

    tester.set_keys(file_path);
    tu.SetKeys(file_path);
}


TEST(TableTrie , build){
    table_trie::TableTrie trie;

    tu.Build(trie);
    tu.SetSavepath(save_path);
    tu.Save(trie);
    std::cout << "\ntabletrie size : " << tu.SizeCalc(trie) << std::endl;

    // trie.Output();
}

TEST(TableTrie, find ) {

    table_trie::TableTrie trie;
    tu.Load(trie , save_path);

    tester.find_test(trie);
}

TEST(TableTrie, dump ) {

    table_trie::TableTrie trie;
    tu.Load(trie , save_path);
    
    tester.dump_test(trie);
}

TEST(TableTrie, find_speed ) {

    table_trie::TableTrie trie;
    tu.Load(trie , save_path);
    
    tester.find_speed_test(trie);
}
