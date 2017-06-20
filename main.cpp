#include <iostream>
#include <map>
#include <vector>
#include "Tester.hpp"
#include "DaTrie.hpp"
#include "TrieUtility.hpp"


void da( std::vector<std::string> args ){

    TrieUtility tu;
    Tester tester;

    tester.set_keys(args[1]);
    tu.SetKeys(args[1]);

    da_trie::DaTrie trie;
    tu.Build(trie);

    tester.find_speed_test(trie);

    tu.Save(trie);
}

int main( int argc , const char* argv[] ) {

    std::cout << "trie samples" << std::endl;
    std::cout << "./trie_samples [mode] [keyset_path]" << std::endl;


    if (argc != 3) {
        std::cerr << "引数が違います\n";
        return 1;
    }


    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
        args.push_back({argv[i]});


    std::map<std::string , int> mode_select;
    mode_select.insert( std::make_pair( "da" , 0) );
    mode_select.insert( std::make_pair( "list" , 1) );
    mode_select.insert( std::make_pair( "table" , 2) );


    switch( mode_select[ args[0] ] ){

        case 0:
            da(args);
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }

    return 0;
}