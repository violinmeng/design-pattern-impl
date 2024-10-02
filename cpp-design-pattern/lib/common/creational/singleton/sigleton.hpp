#pragma once

#include <string>
#include <iostream>
#include <mutex>

namespace DesignPattern {
// https://stackoverflow.com/questions/2576022/how-do-you-implement-a-singleton-efficiently-and-thread-safely
// https://www.modernescpp.com/index.php/thread-safe-initialization-of-data/
// https://mysteriouspreserve.com/blog/2021/09/20/Cpp-and-the-Perils-of-Double-Checked-Locking/

class Singleton
{

protected:
    Singleton(const std::string value): value_(value)
    {
    }
    static Singleton* singleton_;
    static std::mutex mutex_; // for thread safety implementation
    std::string value_;

public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    static Singleton &GetInstance(const std::string& value);
    static Singleton &GetInstanceThreadSafety(const std::string& value);

    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */
    void call()
    {
        std::cout << "Singleton: calling \n";
    }

    std::string value() const
    {
        return value_;
    } 
};

Singleton& Singleton::GetInstance(const std::string& value)
{
    // for c++11, Object initialization will be made only by one thread, 
    // other threads will wait till it complete.
    // Or you can use std::call_once. 
    static Singleton inst(value);
    return inst;
}

Singleton* Singleton::singleton_{nullptr};
std::mutex Singleton::mutex_;

Singleton& Singleton::GetInstanceThreadSafety(const std::string& value)
{
    // double check locking
    if (singleton_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (singleton_ == nullptr) {
            singleton_ = new Singleton(value);
        }
    }
    return *singleton_;
}
}