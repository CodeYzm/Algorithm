#include<iostream>
using namespace std;

// 引用计数类
class RefCount {
private:
	int count{1};
public:
	int use_count() const noexcept { return count; }
	void dec_count()noexcept { --count; }
	void inc_count()noexcept { ++count; }
};

// shared_ptr类模板
template<class T>
class SharedPtr {
private:
	T* origin_ptr{ nullptr }; // 原始指针
	RefCount* refCount{ nullptr }; // 引用计数
public:
	SharedPtr()noexcept = default; // 默认构造
	SharedPtr(nullptr_t)noexcept :SharedPtr() {} // 空指针构造
	explicit SharedPtr(T* ptr)noexcept :origin_ptr(ptr), refCount(nullptr){ // 用原始指针作为参数构造
		if (origin_ptr != nullptr) refCount = new RefCount();
	}
	SharedPtr(const SharedPtr& ptr)noexcept :origin_ptr(ptr.origin_ptr), refCount(ptr.refCount) { // 拷贝构造
		if(origin_ptr != nullptr) refCount->inc_count();
	}
	SharedPtr(SharedPtr&& ptr)noexcept :origin_ptr(ptr.origin_ptr), refCount(ptr.refCount) { // 移动构造
		ptr.origin_ptr = nullptr;
		ptr.refCount = nullptr;
	}
	~SharedPtr()noexcept { // 析构函数
		if (origin_ptr != nullptr && refCount->use_count() == 0) {
			delete origin_ptr;
			delete refCount;
			origin_ptr = nullptr;
			refCount = nullptr;
		}
	}
	SharedPtr& operator=(const SharedPtr& rhs)noexcept { // 拷贝赋值运算符重载
		SharedPtr(rhs).swap(*this);
		return *this;
	}
	SharedPtr& operator=(SharedPtr&& rhs)noexcept { // 移动赋值运算符重载
		SharedPtr(move(rhs)).swap(*this);
		return *this;
	}
	T& operator->() const noexcept{ // 指针运算符重载
		return origin_ptr;
	}
	T& operator*() const noexcept { // 解引用运算符重载
		return *origin_ptr;
	}

public: // 以下是提供的接口函数
	T* get()const noexcept { // get()函数获取原始指针对象
		return origin_ptr;
	}
	int use_count() const noexcept { // use_count()函数获取引用计数
		return origin_ptr == nullptr ? 0 : refCount->use_count();
	}
	void reset()noexcept { // reset()重置指针
		SharedPtr().swap(*this);
	}
	void reset(nullptr_t) noexcept {
		reset();
	}
	void reset(T* ptr)noexcept {
		SharedPtr(ptr).swap(*this);
	}
	bool unique()noexcept { // unique() 查看是否资源独有
		return refCount == nullptr ? false : (refCount->use_count() == 1);
	}
	void swap(SharedPtr& rhs) noexcept{ // swap()交换对象内容
		using std::swap; // 令std::swap在此函数内可用，不显示指定std中的swap版本是为了防止T专属的swap版本得不到调用
		swap(origin_ptr, rhs.origin_ptr); 
		swap(refCount, rhs.refCount);
	}
};



//int main() {
//	int* a = new int(2);
//	SharedPtr<int>p(a); //测试构造函数
//	cout << p.use_count() << endl;
//	cout << *p << endl;
//	SharedPtr<int>q(p); //测试拷贝构造
//	cout << p.use_count() << endl;
//	cout << q.use_count() << endl;
//	SharedPtr<int>n = p; //测试赋值运算符
//	cout << p.use_count() << endl;
//	cout << n.use_count() << endl;
//	SharedPtr<int>m = move(p); //测试右值引用赋值运算符
//	cout << q.use_count() << endl;
//	// cout << p.get_count() << endl;
//	q.reset();
//	cout << q.get() << endl;
//	return 0;
//}