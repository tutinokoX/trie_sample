/*
 * main.cpp
 * */

#include <gtest/gtest.h>
#include "DaTrie.hpp"
#include "Tester.hpp"
#include "TrieUtility.hpp"

// using namespace list_trie;
// using namespace table_trie;

namespace {

    Tester tester;
    TrieUtility tu;
}

TEST(Trie , build){

    std::string file_path;
    std::cout << "keyset path \n ->";
    std::cin >> file_path;

    tester.set_keys(file_path);
    tu.SetKeys(file_path);
}


TEST(ListTrie, all ) {

    da_trie::DaTrie trie;
    tu.Build(trie);


}
