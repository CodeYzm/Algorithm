// �������ڣ�2022-07-13
// ���ߣ�YZM
// �ο���https://github1s.com/ACking-you/my_tiny_stl/blob/HEAD/src/Data_struct_tool/HashTable/sample_HashMap.h
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
	const static int init_buckets_size = 49; // Ͱ�ĳ�ʼ����
	int buckets_size; // Ͱ������
	int keys_count; // key������
	vector<Node<T>>buckets; // �������ָ�����ͣ���ȥ��ʼ���Ĳ���
	int hashfun(T val); // ��ϣ����
public:
	HashTable();
	~HashTable();
	int& operator[](int index) const; // ����[]���������ϣ����ʱ�ò���
	void insert(T val); // ����
	void erase(T val); // ɾ��
	bool find(T val); // Ѱ��
	void expand(); // ����
	void clear(); // ��ղ��ͷ���Դ
	void print(); // ��ӡ���
};
#endif 

