/*
 * main.cpp
 * */

#include <gtest/gtest.h>
#include <ComListTrie.hpp>
#include "ListTrie.hpp"
#include "ComListTrie.hpp"
#include "Tester.hpp"
#include "TrieUtility.hpp"


namespace {

    Tester tester;
    TrieUtility tu;
    std::string save_path = "../test/_savedic/listtrie.dic";
}

TEST(ListTrie , keyset){

    std::string file_path;
    std::cout << "keyset path \n ->";
    std::cin >> file_path;
    // file_path = "../../../test/keyset/wordnet-3.0-word-100000";

    tester.set_keys(file_path);
    tu.SetKeys(file_path);
}


TEST(ListTrie , build){
    com_list_trie::ComListTrie trie;

    std::cout << "ポインタではなく配列のインデックス番号を使用したComListTrie" << std::endl;

    tu.Build(trie);
    tu.SetSavepath(save_path);
    tu.Save(trie);
    std::cout << "\nlisttrie size : " << tu.SizeCalc(trie) << std::endl;


    // trie.Output();
}

TEST(ListTrie, find ) {

    com_list_trie::ComListTrie trie;
    tu.Load(trie , save_path);

    tester.find_test(trie);
}

TEST(ListTrie, dump ) {

    com_list_trie::ComListTrie trie;
    tu.Load(trie , save_path);

    tester.dump_test(trie);
}

TEST(ListTrie, find_speed ) {

    com_list_trie::ComListTrie trie;
    tu.Load(trie , save_path);

    tester.find_speed_test(trie);
}
