#ifndef _CACULATOR
#define _CACULATOR
using namespace std;
static int tt = 10;
template<class T>
class Caculator {
public:
    virtual T caculate(const T& a, const T& b) = 0;
};

template<class T>
class Adder : public Caculator<T> {
public:
    T caculate(const T& a, const T& b);
};

template<class T>
class Minuser : public Caculator<T> {
public:
    T caculate(const T& a, const T& b);
};

template<class T>
class Muliplier : public Caculator<T> {
public:
    T caculate(const T& a, const T& b);
};

template<class T>
class Divider : public Caculator<T> {
public:
    T caculate(const T& a, const T& b);
};



template<class T>
T Adder<T>::caculate(const T& a, const T& b) {
    return a + b;
}

template<class T>
T Minuser<T>::caculate(const T& a, const T& b) {
    return a - b;
}

template<class T>
T Muliplier<T>::caculate(const T& a, const T& b) {
    return a * b;
}

template<class T>
T Divider<T>::caculate(const T& a, const T& b) {
    return a / b;
}


#endif