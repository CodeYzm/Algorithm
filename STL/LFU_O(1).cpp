#include<iostream>
#include<unordered_map>
using namespace std;
constexpr int default_capacity = 50;

struct Node {
	int freq, key, val;
	Node() :freq(0), key(0), val(0) {};
	Node(int _key, int _val, int _freq) :key(_key), val(_val), freq(_freq) {};
};

class LFU {
private:
	unordered_map<int, list<Node>::iterator>key_table; // 键值是key
	unordered_map<int, list<Node>>freq_table; // 键值是访问频率
	int minFreq, capacity; // 最小访问频率，缓存容量
public:
	LFU() :minFreq(1), capacity(default_capacity) {}
	LFU(int _capacity) :minFreq(1), capacity(_capacity) {}
	void put(int key, int value) {
		if (key_table.find(key) != key_table.end()) {
			auto node = key_table[key];
			int freq = node->freq;
			freq_table[freq].erase(node);
			if (freq_table[freq].size() == 0) {
				freq_table.erase(freq);
				if (freq == minFreq) ++minFreq;
			}
			freq_table[++freq].push_front(Node(key, value, freq)); // 这里不能直接对node进行修改然后push_front(*node)，原因不明，可能跟iterator源码有关
			key_table[key] = freq_table[freq].begin();
		}
		else {
			if (key_table.size() == capacity) { // 提前判断缓存是否会溢出，一是顺序合理，二是防止缓存刚插入(freq = 1)就被去掉
				key_table.erase(freq_table[minFreq].back().key); 
				freq_table[minFreq].pop_back();
				if (freq_table[minFreq].size() == 0) {
					freq_table.erase(minFreq);
				}
			}
			minFreq = 1; // 既然插入了新元素那么minFreq自然就回归1了
			freq_table[1].push_front(Node(key, value, 1));
			key_table[key] = freq_table[1].begin();
		}
	}

	int get(int key) {
		if (key_table.find(key) != key_table.end()) {
			auto node = key_table[key];
			int freq = node->freq, val = node->val;
			freq_table[freq].erase(node);
			if (freq_table[freq].size() == 0) { // 如果当前频率的list空了，则要删除当前list并且判断是否需要更新minFreq
				freq_table.erase(freq);
				if (freq == minFreq) ++minFreq;
			}
			freq_table[++freq].push_front(Node(key,val,freq));
			key_table[key] = freq_table[freq].begin();
			return val;
		}
		return -1;
	}

	void print() { // 打印检查
		for (auto it = key_table.begin(); it != key_table.end(); ++it) {
			cout << it->second->key << " " << minFreq << " " << it->second->freq << endl;
		}
	}
};

//int main() {
//	LFU lfu(2);
//	lfu.put(1, 1);
//	lfu.put(2, 2);
//	lfu.print();
//	lfu.get(1);
//	lfu.get(2);
//	lfu.print();
//	lfu.put(3, 1);
//	lfu.print();
//	lfu.put(3, 2);
//	return -1;
//}