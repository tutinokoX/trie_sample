//
// Created by ydoi-mac on 2017/05/22.
//

#ifndef TRIE_SAMPLE_DATRIEBUILDER_HPP
#define TRIE_SAMPLE_DATRIEBUILDER_HPP

#include <iostream>
#include <vector>
#include <map>
// #include <queue>
#include <stack>
#include "ListTrie.hpp"
#include "ListTrieBuilder.hpp"
#include "StateOut.hpp"

namespace da_trie{

    using refer = int64_t;
    using da_refer = refer;
    using trie_refer = list_trie::refer;



    class TrieForDa : public list_trie::ListTrie{

    private:

        struct order_unit{
            trie_refer  trie_index;
            da_refer    da_index;
        };

        std::stack<trie_refer> ORDER;
        std::map<trie_refer , da_refer> MATCH;

        // trieとdaのインデックス番号を対応を保存方法を検討中

        StateOut so;
        size_t counter = 0;


    public:

        TrieForDa(){

            ORDER.push(ROOT);
            MATCH.insert(std::make_pair( ROOT , 0 ));

        }


        std::vector<uint8_t> Labels( trie_refer trie_current ){

            std::vector<uint8_t> buf;
            trie_refer ptr = trie_current->child;
            while(1){
                if( ptr == FREE ) break;

                buf.push_back( ptr->label );
                ptr = ptr->sib;
            }

            return buf;
        }


        void Start( std::vector<std::string> keyset ){

            StaticInsert(keyset);
            so.AddMaxState( (size_t)NodeNum() - keyset.size() );
            so.StartSet();
        }

        bool NodeGet( trie_refer &trie_index , da_refer &da_index ){

            while(1) {
                if (ORDER.empty())
                    return false;

                trie_index = ORDER.top();
                ORDER.pop();

                da_index = MATCH[trie_index];
                MATCH.erase(trie_index);


                if (EndCheck(trie_index)) {


                    if (!IsTerm()) continue;   // 終端フラグならこの処理は必要なし : 動的に変更するように検討
                }


                std::vector<uint8_t>
                labels = Labels(trie_index);

                for (auto label : labels) {
                    trie_refer next = Goto(trie_index, label);
                    if (NextCheck(next)) {
                        ORDER.push(next);
                        MATCH.insert(std::make_pair(next, 0));
                    }
                }

                counter ++;
                so.Output(counter);
                return true;
            }
        }


        void IndexSet(trie_refer ptr , uint8_t label , da_refer da_index){

            ptr = ptr->child;
            while(1){
                if(label == ptr->label){

                    // ここの処理が少し重いかも（基本stackだから順番通りだけど）
                    if( MATCH.find(ptr) != MATCH.end() ){
                        MATCH[ptr] = da_index;
                    }
                    return;
                }

                if(ptr->sib == nullptr){
                    std::cerr << "err !! : ListTrie/SetIndex \n";
                    exit(1);
                }

                ptr = ptr->sib;
            }
        }

        da_refer NodeNum(){

            da_refer count = 1;
            std::stack<trie_refer> searcher;
            searcher.push(ROOT);

            while(1) {
                if (searcher.empty()) break;
                trie_refer trie_index = searcher.top();
                searcher.pop();

                if (EndCheck(trie_index)) {
                    if (!IsTerm()) continue;   // 終端フラグならこの処理は必要なし : 動的に変更するように検討
                }

                std::vector<uint8_t> labels = Labels(trie_index);

                for (auto label : labels) {
                    trie_refer next = Goto(trie_index, label);
                    if (NextCheck(next)) {
                        searcher.push(next);
                        count++;
                    }
                }
            }

            return count;
        }

    };


    class TempListUnit{
    private:
        da_refer next_;
        da_refer prev_;
        bool fixed;

    public:

        TempListUnit() : next_(0) , prev_(0) , fixed(false) {}

        void clear(){
            next_ = 0;
            prev_ = 0;
        }

        void set_is_fixed(){fixed = true;}
        void set_next(da_refer _next){next_ = _next;}
        void set_prev(da_refer _prev){prev_ = _prev;}

        bool is_fixed() const {return fixed;}
        da_refer next(){return next_;}
        da_refer prev(){return prev_;}

    };




    class DaTrieBuilder{

    private:

        void FirstMemoryAllocation();

        bool ElementSearch(trie_refer tire_index , da_refer da_index );
        da_refer BaseSearch(trie_refer trie_index );
        void ArraySet( da_refer offset , da_refer da_index , trie_refer trie_index );
        void MemoryAllocation( size_t index );
        bool IsValidOffset(da_refer index );


        void TempListResize( size_t index );

        TrieForDa trie;
        std::vector<uint8_t> Labels;

    protected:
        std::vector<da_refer> BASE;
        std::vector<da_refer> CHECK;

        std::vector<TempListUnit> TEMP_LIST;

        char END_CHAR = '#';
        uint8_t END_LABEL = '#';
        da_refer ROOT = 0;
        da_refer FREE = -2;
        da_refer TERM = -1;



    public:

        DaTrieBuilder(){}
        ~DaTrieBuilder(){}

        bool StaticInsert(std::vector<std::string> keyset);
        bool DynamicInsert(std::string str);

        void Output();

        void Dicsave(std::string file_path);
    };


    void DaTrieBuilder::Dicsave(std::string file_path) {


        std::cout << "base  size : " << BASE.size() << "\n";
        std::cout << "check size : " << CHECK.size() << "\n";

        // とりあえずデータの保存は後回し



    }

    bool DaTrieBuilder::StaticInsert(std::vector <std::string> keyset) {

        // trieを構築
        trie.Start( keyset );

        // std::cout << "node num : " << trie.NodeNum() << "\n";

        FirstMemoryAllocation();

        da_refer   da_index;
        trie_refer trie_index;

        while(1){

            // std::cout << "NodeGet\n";
            if( !trie.NodeGet( trie_index , da_index ) ) break;

            // std::cout << "ElementSearch\n";
            ElementSearch(trie_index , da_index);

        }

        return true;
    }


    bool DaTrieBuilder::DynamicInsert(std::string str) {

        std::cerr << " key :  " << str << std::endl;
        std::cerr << "動的構築は実装されていません\n";
        return false;
    }


    void DaTrieBuilder::FirstMemoryAllocation() {

        size_t node_num = static_cast<size_t>(trie.NodeNum());
        BASE.reserve( node_num );
        CHECK.reserve( node_num );
        TEMP_LIST.reserve( node_num );


        size_t size = 255;

        BASE.resize(size , -2);
        CHECK.resize(size , -1);
        TEMP_LIST.resize(1);

        TempListResize(size);
        TEMP_LIST[0].set_is_fixed();
    }


    bool DaTrieBuilder::ElementSearch( trie_refer trie_index , da_refer da_index ) {

        da_refer offset = BaseSearch( trie_index  );
        ArraySet(offset , da_index , trie_index);

        return true;
    }

    da_refer DaTrieBuilder::BaseSearch( trie_refer trie_index  ) {


        Labels = trie.Labels(trie_index);

        // ラベル最大値を確認
        // uint8_t max_label = std::max(labels);

        da_refer unfixed_index = 0;
        da_refer num_units = static_cast<da_refer >( TEMP_LIST.size() );

        while(1) {
            if(unfixed_index >= num_units ) break;
            unfixed_index = TEMP_LIST[static_cast<size_t >(unfixed_index)].next();

            if(unfixed_index == 0) break;
            da_refer offset = unfixed_index - Labels[0];    // ここでマイナスが出力される可能性あり

            if (IsValidOffset(offset))
                return offset;
        }

        return num_units;
    }

    bool DaTrieBuilder::IsValidOffset( da_refer offset ) {

        if(offset < 0) return false;

        for(size_t li = 0 ; li < Labels.size() ; li++ ){

            if( offset + Labels[li] < static_cast<da_refer >( TEMP_LIST.size() ) )
                if( TEMP_LIST[ static_cast<size_t>(offset + Labels[li]) ].is_fixed() ) return false;
        }

        return true;
    }


    void DaTrieBuilder::ArraySet(da_refer offset , da_refer da_index , trie_refer trie_index){

        BASE[ static_cast<size_t>(da_index) ] = offset;

        for(size_t li = 0 ; li < Labels.size() ; li++){

            size_t da_child_index = static_cast<size_t >( offset + Labels[li] );

            MemoryAllocation( da_child_index );

            CHECK[ da_child_index ] = da_index;

            TEMP_LIST[da_child_index].set_is_fixed();

            if(TEMP_LIST[ da_child_index ].prev() == 0) {
                std::cout << "prev 0";
            }

            if(TEMP_LIST[ da_child_index ].next() == 0) {
                // std::cout << "next 0";
            }



            TEMP_LIST[ static_cast<size_t >( TEMP_LIST[da_child_index].prev() ) ].set_next( TEMP_LIST[da_child_index].next() );
            TEMP_LIST[ static_cast<size_t >( TEMP_LIST[da_child_index].next() ) ].set_prev( TEMP_LIST[da_child_index].prev() );

            TEMP_LIST[ da_child_index ].clear();


            // 終端文字処理
            if(Labels[li] == END_LABEL){

                BASE[da_child_index] = TERM;
            }
            trie.IndexSet( trie_index , Labels[li] , static_cast<da_refer >(da_child_index) );

        }
    }

    void DaTrieBuilder::MemoryAllocation( size_t index ) {

        // std::cout << "MA s_state.max_next : " << s_state.max_next << "\n";
        // std::cout << "MA buf_task.size : " << s_state.buf_task.size() << "\n";

        if( index < TEMP_LIST.size() ) return;
        size_t size = index+1;

        // std::cout << "MA reseize\n";
        {
            CHECK.resize(size, -1);
            BASE.resize(size, -2);
            TempListResize(size);
        }
    }

    void DaTrieBuilder::TempListResize( size_t index ) {

        da_refer index_ = static_cast<da_refer >(TEMP_LIST.size());
        TEMP_LIST.resize( index );

        for(size_t i = static_cast<size_t >(index_+1) ; i < index ; i++){

            TEMP_LIST[i - 1].set_next( static_cast<da_refer >(i) );
            TEMP_LIST[i].set_prev( static_cast<da_refer >(i - 1) );
        }

        TEMP_LIST[ static_cast<size_t >(TEMP_LIST[0].prev()) ].set_next(index_);
        TEMP_LIST[ static_cast<size_t >(index_) ].set_prev(TEMP_LIST[0].prev());
        TEMP_LIST[0].set_prev( static_cast<da_refer >(index -1) );

    }


    void DaTrieBuilder::Output() {

        if (BASE.size() > 1000) {
            std::cerr << "OrDa/Output\n";
            std::cerr << "size over ( ~1000 ) -> " << BASE.size() << "\n";
            return;
        }

        size_t wrap = 25;

        for (size_t ti = 0; ti < TEMP_LIST.size() ; ti++) {

            if (ti % wrap == 0) std::cout << "\n\n  " << ti << "\t: ";
            if(!TEMP_LIST[ti].is_fixed()) continue;
            std::cout << BASE[ti] << "|" << CHECK[ti] << "\t";

        }
        std::cout << '\n';

    }

}

#endif //TRIE_SAMPLE_DATRIEBUILDER_HPP
