#include<iostream>
using namespace std;

// ���ü�����
class RefCount {
private:
	int count{1};
public:
	int use_count() const noexcept { return count; }
	void dec_count()noexcept { --count; }
	void inc_count()noexcept { ++count; }
};

// shared_ptr��ģ��
template<class T>
class SharedPtr {
private:
	T* origin_ptr{ nullptr }; // ԭʼָ��
	RefCount* refCount{ nullptr }; // ���ü���
public:
	SharedPtr()noexcept = default; // Ĭ�Ϲ���
	SharedPtr(nullptr_t)noexcept :SharedPtr() {} // ��ָ�빹��
	explicit SharedPtr(T* ptr)noexcept :origin_ptr(ptr), refCount(nullptr){ // ��ԭʼָ����Ϊ��������
		if (origin_ptr != nullptr) refCount = new RefCount();
	}
	SharedPtr(const SharedPtr& ptr)noexcept :origin_ptr(ptr.origin_ptr), refCount(ptr.refCount) { // ��������
		if(origin_ptr != nullptr) refCount->inc_count();
	}
	SharedPtr(SharedPtr&& ptr)noexcept :origin_ptr(ptr.origin_ptr), refCount(ptr.refCount) { // �ƶ�����
		ptr.origin_ptr = nullptr;
		ptr.refCount = nullptr;
	}
	~SharedPtr()noexcept { // ��������
		if (origin_ptr != nullptr && refCount->use_count() == 0) {
			delete origin_ptr;
			delete refCount;
			origin_ptr = nullptr;
			refCount = nullptr;
		}
	}
	SharedPtr& operator=(const SharedPtr& rhs)noexcept { // ������ֵ���������
		SharedPtr(rhs).swap(*this);
		return *this;
	}
	SharedPtr& operator=(SharedPtr&& rhs)noexcept { // �ƶ���ֵ���������
		SharedPtr(move(rhs)).swap(*this);
		return *this;
	}
	T& operator->() const noexcept{ // ָ�����������
		return origin_ptr;
	}
	T& operator*() const noexcept { // ���������������
		return *origin_ptr;
	}

public: // �������ṩ�Ľӿں���
	T* get()const noexcept { // get()������ȡԭʼָ�����
		return origin_ptr;
	}
	int use_count() const noexcept { // use_count()������ȡ���ü���
		return origin_ptr == nullptr ? 0 : refCount->use_count();
	}
	void reset()noexcept { // reset()����ָ��
		SharedPtr().swap(*this);
	}
	void reset(nullptr_t) noexcept {
		reset();
	}
	void reset(T* ptr)noexcept {
		SharedPtr(ptr).swap(*this);
	}
	bool unique()noexcept { // unique() �鿴�Ƿ���Դ����
		return refCount == nullptr ? false : (refCount->use_count() == 1);
	}
	void swap(SharedPtr& rhs) noexcept{ // swap()������������
		using std::swap; // ��std::swap�ڴ˺����ڿ��ã�����ʾָ��std�е�swap�汾��Ϊ�˷�ֹTר����swap�汾�ò�������
		swap(origin_ptr, rhs.origin_ptr); 
		swap(refCount, rhs.refCount);
	}
};



//int main() {
//	int* a = new int(2);
//	SharedPtr<int>p(a); //���Թ��캯��
//	cout << p.use_count() << endl;
//	cout << *p << endl;
//	SharedPtr<int>q(p); //���Կ�������
//	cout << p.use_count() << endl;
//	cout << q.use_count() << endl;
//	SharedPtr<int>n = p; //���Ը�ֵ�����
//	cout << p.use_count() << endl;
//	cout << n.use_count() << endl;
//	SharedPtr<int>m = move(p); //������ֵ���ø�ֵ�����
//	cout << q.use_count() << endl;
//	// cout << p.get_count() << endl;
//	q.reset();
//	cout << q.get() << endl;
//	return 0;
//}