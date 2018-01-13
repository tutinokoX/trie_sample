/*
 * main.cpp
 * */

#include <gtest/gtest.h>
#include <ComListTrie.hpp>
#include "ListTrie.hpp"
#include "TableTrie.hpp"
#include "ComListTrie.hpp"
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
/*
    list_trie::ListTrie list;
    tu.Build(list);

    tester.find_test(list);
    tester.dump_test(list);
    tester.find_speed_test(list);
*/
}

TEST(TableTrie , all ){
/*
    table_trie::TableTrie table;
    tu.Build(table);

    tester.find_test(table);
    tester.dump_test(table);
    tester.find_speed_test(table);
*/
}

TEST(ComListTrie , all ){

    com_list_trie::ComListTrie clist;
    tu.Build(clist);

    tester.find_test(clist);
    tester.dump_test(clist);
    tester.find_speed_test(clist);
}
