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
    // file_path = "/Users/ydoi/Documents/study/xsda-dev/test/_KEYSET/paper_keyset";

    tester.set_keys(file_path);
    tu.SetKeys(file_path);
}


TEST(DaTrie, all ) {

    da_trie::DaTrie trie;
    tu.Build(trie);
    // trie.Output();

    tester.find_test(trie);
    tester.dump_test(trie);
    tester.find_speed_test(trie);

}
