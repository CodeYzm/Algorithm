// 创建日期：2022-07-13
// 作者：YZM
// 参考：https://github1s.com/ACking-you/my_tiny_stl/blob/HEAD/src/Data_struct_tool/HashTable/sample_HashMap.h
#pragma once
#ifndef SAMPLE_HASHMAP_H
#define SAMPLE_HASHMAP_H

#include<iostream>
#include<vector>
using namespace std;

template<typename T>
struct Node {
	Node* next;
	T val;
	Node() :next(nullptr), val(0) {};
	Node(T _val) :next(nullptr), val(_val) {};
	Node(T _val, Node* nxt) :next(nxt), val(_val) {};
};

template<typename T>
class HashTable {
private:
	const static int init_buckets_size = 49; // 桶的初始数量
	int buckets_size; // 桶的数量
	int keys_count; // key的数量
	vector<Node<T>>buckets; // 不定义成指针类型，免去初始化的步骤
	int hashfun(T val); // 哈希函数
public:
	HashTable();
	~HashTable();
	int& operator[](int index) const; // 重载[]运算符，哈希表暂时用不到
	void insert(T val); // 插入
	void erase(T val); // 删除
	bool find(T val); // 寻找
	void expand(); // 扩容
	void clear(); // 清空并释放资源
	void print(); // 打印检查
};
#endif 

