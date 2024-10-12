#pragma once

#include <vector>
#include <memory>
#include <iostream>

// Iterator is a behavioral design pattern
// that lets you traverse elements of a collection
// without exposing its underlying representation (list, stack, tree, etc.).

namespace DesignPattern
{

template <typename T, typename U>
class Iterator {
public:
    using IterType = typename std::vector<T>::iterator;
    Iterator(U* pData, bool reverse = false) : pData(pData) {
        it = pData->data.begin();
    }
    void first() {
        it = pData->data.begin();
    }
    void next() {
        it++;
    }
    bool isDone() {
        return (it == pData->data.end());
    }
    IterType current() {
        return it;
    }
private:
    U* pData;
    IterType it;
};

template<typename T>
class Container {
    friend class Iterator<T, Container>;
private:
    std::vector<T> data;
public:
    void add(T element) {
        data.push_back(element);
    }
    std::unique_ptr<Iterator<T, Container>> createIterator() {
        return std::make_unique<Iterator<T, Container>>(this);
    }
};

class TData {
private:
    int value;
public:
    TData(int val = 0) : value(val) {}
    void setValue(int val) {
        value = val;
    }
    int getValue() {
        return value;
    }
};

void iteratorClientCode() {
    std::cout << "________________Iterator with int______________________________________" << std::endl;
    Container<int> cont;

    for (int i = 0; i < 10; i++) {
        cont.add(i);
    }

    auto it = cont.createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        std::cout << *it->current() << std::endl;
    }

    Container<TData> cont2;
    TData test1(100), test2(1000), test3(10000);
    cont2.add(test1);
    cont2.add(test2);
    cont2.add(test3);

    std::cout << "________________Iterator with custom Class______________________________" << std::endl;
    auto it2 = cont2.createIterator();
    for (it2->first(); !it2->isDone(); it2->next()) {
        std::cout << it2->current()->getValue() << std::endl;
    }
}

} // namespace DesignPattern
