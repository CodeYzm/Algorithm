#include<iostream>
#include<set>
#include<unordered_map>
using namespace std;
constexpr int default_capacity = 50; // 默认缓存容量
struct Node {
	int freq, time, key, val;
	Node():freq(1), key(0), val(0), time(0) {}; // 这里注意，虽然代码中默认构造函数根本没用到，但是hash_map在重载[]运算符的时候要用到T()，也就是Node()
	Node(int _key, int _val, int _time) :freq(1), key(_key), val(_val), time(_time){};
	bool operator < (const Node& rhs) const { // 重载 < 运算符，设置成常函数
		return freq == rhs.freq ? time < rhs.time : freq < rhs.freq;
	}
};
class LFU {
private:
	unordered_map<int, Node>key_table;
	set<Node>freq_set; // 利用set红黑树的性质，通过重载<运算符对Node在freq_set内部进行排序
	int time; // 时间戳
	int capacity; // 缓存容量
public:
	LFU():capacity(default_capacity), time(0) {}
	LFU(int _capacity):capacity(_capacity), time(0) {}
	~LFU() {}
	void put(int key, int value) {
		if (key_table.find(key) != key_table.end()) {
			Node node = key_table[key];
			freq_set.erase(node);
			++node.freq; // 更新访问频率
			node.val = value; // 更新值
			node.time = ++time; // 更新时间戳
			key_table[key] = node; // 由于node是临时对象，所以更新完node后要重新插入set和map
			freq_set.insert(node);
		}
		else {
			if (key_table.size() == capacity) { // 缓存满了
				auto node = freq_set.begin(); // 头指针，指向最少访问或者最早添加的缓存
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

	void print() { // 打印检查
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