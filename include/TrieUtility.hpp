//
// Created by ydoi-mac on 2017/05/10.
//

#ifndef XSDA_DEV_TRIEUTILITY_HPP
#define XSDA_DEV_TRIEUTILITY_HPP


class TrieUtility {

private:

    std::vector<std::string> _KEYSET;

    std::string save_path;

    void read_keys(std::string file_path, std::vector<std::string> &KEYSET) {

        std::ifstream ifs(file_path);
        if (ifs.fail()) {
            std::cerr << " read_keys " << std::endl;
            std::cerr << " err : file open -> " << file_path << std::endl;
            exit(1);
        }
        std::string key;
        while (getline(ifs, key)) KEYSET.push_back(key);
        sort(KEYSET.begin(), KEYSET.end());
        KEYSET.erase(unique(KEYSET.begin(), KEYSET.end()), KEYSET.end());
    }


public:


    void SetKeys(std::string file_path) {

        read_keys(file_path, _KEYSET);
    }

    void SetSavepath(std::string file_path) {

        save_path = file_path;
    }

    template<class T>
    void ConfSplit(T &trie, std::string value) {

        std::string data;
        std::vector<std::string> buf;
        std::stringstream ss(value);
        while (getline(ss, data, '_')) {
            buf.push_back(data);
        }
        trie.Setup_SPLIT_NUM(std::stoi(buf[0]));
        trie.Setup_LIMIT_PER(std::stod(buf[1]));
    }


    /*
     * 静的と動的の区別をつけれるようにするべきかも
     */
    template<class T>
    void Build(T &trie) {

        trie.StaticInsert(_KEYSET);
    }


    template<class T>
    void Save(T &trie) {

        if (save_path.empty()) {
            std::cout << "save path \n -> ";
            std::cin >> save_path;
        }
        trie.Dicsave(save_path);
    }

    
    template<class T>
    void Load(T &trie, std::string load_path = "") {

        if (load_path == "") {
            std::cout << "load path \n -> ";
            std::cin >> load_path;
        }
        trie.Dicload(load_path);
    }

    template<class T>
    std::string SizeCalc(T &trie) {

        return std::to_string(trie.SizeCalc()) + " [MByte]";
    }

};

#endif //XSDA_DEV_TRIEUTILITY_HPP
