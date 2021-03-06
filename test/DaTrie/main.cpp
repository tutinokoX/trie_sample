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
    std::string save_path = "../test/_savedic/datrie.dic";
}

TEST(DaTrie , keyset){

    std::string file_path;
    std::cout << "keyset path \n ->";
    std::cin >> file_path;
    // file_path = "/Users/ydoi/Documents/study/xsda-dev/test/_KEYSET/paper_keyset";

    tester.set_keys(file_path);
    tu.SetKeys(file_path);
}


TEST(DaTrie , build){
    da_trie::DaTrie trie;

    tu.Build(trie);
    tu.SetSavepath(save_path);
    tu.Save(trie);
    std::cout << "\nda size : " << tu.SizeCalc(trie) << std::endl;
    // trie.Output();
}

TEST(DaTrie, find ) {

    da_trie::DaTrie trie;
    tu.Load(trie , save_path);

    tester.find_test(trie);
}

TEST(DaTrie, dump ) {

    da_trie::DaTrie trie;
    tu.Load(trie , save_path);

    tester.dump_test(trie);
}

TEST(DaTrie, find_speed ) {

    da_trie::DaTrie trie;
    tu.Load(trie , save_path);

    tester.find_speed_test(trie);
}
