# Trieサンプル

## 概要
Trieの研究に当たって，比較対象を整理する
- table : 二次元配列
- list : リンク
- da : ダブル配列

それぞれのトライ構造に対して，検索速度と記憶領域の比較を行う

## 環境
必要なもの
- cmake
- gtest

## コンパイル
```
mkdir build && cd $_
cmake ..
make
```

## 実行
#### ベンチマーク
```
pwd ~/trie_sample/build
./test/Benchmark/benchmark
```

#### 各トライに対して
```
pwd ~/trie_sample/build
./test/DaTrie/datrie
./test/ListTrie/listtrie
./test/TableTrie/tabletrie
```
