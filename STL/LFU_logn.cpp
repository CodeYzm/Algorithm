#include<iostream>
#include<set>
#include<unordered_map>
using namespace std;
constexpr int default_capacity = 50; // Ĭ�ϻ�������
struct Node {
	int freq, time, key, val;
	Node():freq(1), key(0), val(0), time(0) {}; // ����ע�⣬��Ȼ������Ĭ�Ϲ��캯������û�õ�������hash_map������[]�������ʱ��Ҫ�õ�T()��Ҳ����Node()
	Node(int _key, int _val, int _time) :freq(1), key(_key), val(_val), time(_time){};
	bool operator < (const Node& rhs) const { // ���� < ����������óɳ�����
		return freq == rhs.freq ? time < rhs.time : freq < rhs.freq;
	}
};
class LFU {
private:
	unordered_map<int, Node>key_table;
	set<Node>freq_set; // ����set����������ʣ�ͨ������<�������Node��freq_set�ڲ���������
	int time; // ʱ���
	int capacity; // ��������
public:
	LFU():capacity(default_capacity), time(0) {}
	LFU(int _capacity):capacity(_capacity), time(0) {}
	~LFU() {}
	void put(int key, int value) {
		if (key_table.find(key) != key_table.end()) {
			Node node = key_table[key];
			freq_set.erase(node);
			++node.freq; // ���·���Ƶ��
			node.val = value; // ����ֵ
			node.time = ++time; // ����ʱ���
			key_table[key] = node; // ����node����ʱ�������Ը�����node��Ҫ���²���set��map
			freq_set.insert(node);
		}
		else {
			if (key_table.size() == capacity) { // ��������
				auto node = freq_set.begin(); // ͷָ�룬ָ�����ٷ��ʻ���������ӵĻ���
				key_table.erase(node->key);
				freq_set.erase(node);
			}
			Node node = Node(key, value, ++time);
			freq_set.insert(node);
			key_table[key] = node;
		}
	}

	int get(int key) {
		if (key_table.find(key) != key_table.end()) {
			Node node = key_table[key];
			freq_set.erase(node);
			++node.freq;
			node.time = ++time;
			freq_set.insert(node);
			key_table[key] = node;
			return node.val;
		}
		return -1;
	}

	void print() { // ��ӡ���
		for (auto it = freq_set.begin(); it != freq_set.end(); ++it) {
			cout << it->key << " " << it->time << " " << it->freq << endl;
		}
	}
};

//int main() {
//	LFU lfu(2);
//	lfu.put(1,1);
//	lfu.put(2, 1);
//	lfu.print();
//	lfu.get(1);
//	lfu.print();
//	lfu.put(3,1);
//	lfu.print();
//	lfu.put(3, 2);
//	return -1;
//}