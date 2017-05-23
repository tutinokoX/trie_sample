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


namespace da_trie{

    using refer = int;
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

    public:

        TrieForDa(){

            ORDER.push(ROOT);
            MATCH.insert(std::make_pair( ROOT , 0 ));
        }

        std::vector<uint8_t> Labels( trie_refer trie_current ){

            std::vector<uint8_t> buf;
            uint8_t label;
            trie_refer ptr = trie_current->child;
            while(1){
                if( ptr == FREE ) break;

                buf.push_back( ptr->label );
                ptr = ptr->sib;
            }

            return buf;
        }


        bool NodeGet( trie_refer &trie_index , da_refer &da_index ){

            if(ORDER.empty())
                return false;

            trie_index = ORDER.top();
            ORDER.pop();

            da_index = MATCH[trie_index];

            /*
            if( trie.EndCheck( current ) ){
                dump_count ++;
                so.Output( dump_count );
                if( !trie.IsTerm() ) continue;   // 終端フラグならこの処理は必要なし : 動的に変更するように検討
            }
            */

            std::vector<uint8_t> labels = Labels(trie_index);

            for(auto label : labels){
                trie_refer next = Goto( trie_index , label );
                if (NextCheck( next )) {
                    ORDER.push( next );
                    MATCH.insert(std::make_pair(next , 0));
                }
            }

            return true;
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

    };


    class TempListUnit{
    private:
        da_refer next_;
        da_refer prev_;
        bool fixed;
        bool used;

    public:

        TempListUnit() : next_(0) , prev_(0) {}

        void clear(){
            next_ = 0;
            prev_ = 0;
            fixed = false;
            used = false;
        }

        void set_is_fixed(){fixed = true;}
        void set_is_used(){used = true;}
        void set_next(da_refer _next){next_ = _next;}
        void set_prev(da_refer _prev){prev_ = _prev;}

        bool is_fixed() const {return fixed;}
        bool is_used() const {return used;}

        da_refer next(){return next_;}
        da_refer prev(){return prev_;}

    };




    class DaTrieBuilder{

    private:

        void FirstMemoryAllocation();

        bool ElementSearch(trie_refer tire_index , da_refer da_index );
        da_refer BaseSearch(trie_refer trie_index , da_refer  da_index );
        void ArraySet( da_refer offset , da_refer da_index , trie_refer trie_index );
        void MemoryAllocation(da_refer index );
        bool IsValidOffset(da_refer index );


        void TempListResize( da_refer index );

        TrieForDa trie;
        std::vector<uint8_t> Labels;

    protected:
        std::vector<da_refer> BASE;
        std::vector<da_refer> CHECK;

        std::vector<TempListUnit> TEMP_LIST;

        uint8_t END_LABEL = '#';
        da_refer TERM = -1;



    public:

        DaTrieBuilder(){}
        ~DaTrieBuilder(){}

        bool StaticInsert(std::vector<std::string> keyset);
        bool DynamicInsert(std::string str);
    };



    bool DaTrieBuilder::StaticInsert(std::vector <std::string> keyset) {

        // trieを構築
        trie.StaticInsert(keyset);

        FirstMemoryAllocation();

        da_refer   da_index;
        trie_refer trie_index;

        while(1){

            // std::cout << "NodeGet\n";
            if( !trie.NodeGet( trie_index , da_index ) ) break;

            // std::cout << "ElementSearch\n";
            ElementSearch(trie_index , da_index);

        }

    }


    bool DaTrieBuilder::DynamicInsert(std::string str) {

        std::cerr << "動的構築は実装されていません\n";
    }


    void DaTrieBuilder::FirstMemoryAllocation() {

        // BASE.reserve(lt->trie_node_num());
        // CHECK.reserve(lt->trie_node_num());

        // size_t size = (KEYSET.size() > CODE.size()) ? KEYSET.size() : CODE.size();

        size_t size = 255;

        BASE.resize(size , -2);
        BASE.resize(size , -1);
        TempListResize(size);
    }


    bool DaTrieBuilder::ElementSearch( trie_refer trie_index , da_refer da_index ) {

        da_refer offset = BaseSearch( trie_index , da_index );
        ArraySet(offset , da_index , trie_index);

        return true;
    }

    da_refer DaTrieBuilder::BaseSearch( trie_refer trie_index , da_refer  da_index ) {


        Labels = trie.Labels(trie_index);

        // ラベル最大値を確認
        // uint8_t max_label = std::max(labels);


        da_refer unfixed_index = 0;
        da_refer num_units = TEMP_LIST[0].prev();

        while(1) {
            if(unfixed_index >= num_units ) break;
            unfixed_index = TEMP_LIST[unfixed_index].next();
            da_refer offset = unfixed_index - Labels[0];    // ここでマイナスが出力される可能性あり

            if (IsValidOffset(offset))
                return offset;
        }

        return num_units;

        /*
        // std::cout << "base\n";
        s_state.base = s_state.search_location - CODE[key_point];
        if ( s_state.search_location < CODE[key_point] ) s_state.base = 0;

        location = s_state.base + CODE[key_point];
        if ( CHECK.size() >(size_t)location )
            if (CHECK[location] >= 0) return false;

        return true;
        */
    }

    bool DaTrieBuilder::IsValidOffset( da_refer offset ) {

        if(offset < 0) return false;

        for(size_t li = 1 ; li < Labels.size() ; li++ ){

            if( offset + Labels[li] < TEMP_LIST[0].prev() )
                if( TEMP_LIST[ offset + Labels[li] ].is_fixed() ) return false;
        }

        return false;
    }


    void DaTrieBuilder::ArraySet(da_refer offset , da_refer da_index , trie_refer trie_index){

        BASE[da_index] = offset;

        for(size_t li = 0 ; li < Labels.size() ; li++){

            da_refer da_child_index = offset + Labels[li];

            MemoryAllocation( da_child_index );

            CHECK[da_child_index] = da_index;

            TEMP_LIST[da_child_index].set_is_fixed();

            TEMP_LIST[ TEMP_LIST[da_child_index].prev() ].set_next( TEMP_LIST[da_child_index].next() );
            TEMP_LIST[ TEMP_LIST[da_child_index].next() ].set_prev( TEMP_LIST[da_child_index].prev() );

            TEMP_LIST[ da_child_index ].clear();


            // 終端文字処理
            if(Labels[li] == END_LABEL){

                BASE[da_child_index] = TERM;
            }
            trie.IndexSet(trie_index , Labels[li] , da_index);

        }
    }

    void DaTrieBuilder::MemoryAllocation( da_refer index ) {

        // std::cout << "MA s_state.max_next : " << s_state.max_next << "\n";
        // std::cout << "MA buf_task.size : " << s_state.buf_task.size() << "\n";

        if( index < TEMP_LIST[0].prev() ) return;
        int size = index + 1;

        // std::cout << "MA reseize\n";
        {
            CHECK.resize(size, -1);
            BASE.resize(size, -2);
            TempListResize(size);
        }
    }

    void DaTrieBuilder::TempListResize( da_refer index ) {

        TEMP_LIST.resize( index );
    }


}

#endif //TRIE_SAMPLE_DATRIEBUILDER_HPP