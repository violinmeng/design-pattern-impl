#pragma once

#include <iostream>
#include <memory>

namespace DesignPattern {

class Subject {
public:
    virtual void request() const = 0;
};

class RealSubject : public Subject {
public:
    RealSubject() = default;
    RealSubject(const RealSubject &other) {
        std::cout << "Copy constructing RealSubject " << "\n";
    }

    void request() const override {
        std::cout << "RealSubject: handling request.\n";
    }
};

class Proxy : public Subject {
private:
    RealSubject &realSubject;

    bool checkAccess() const {
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }
    void logAccess() const { std::cout << "Proxy: Logging the time of request.\n"; }
public:
    Proxy(RealSubject &realSubject) : realSubject(realSubject) {}

    void request() const override {
        if (this->checkAccess()) {
            this->realSubject.request();
            this->logAccess();
        }
    }
};

void proxyClientCode() {
    std::cout << "Client: Executing the client code with a real subject:\n";
    auto realObject = std::make_unique<RealSubject>();
    realObject->request();
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    auto proxy = std::make_unique<Proxy>(*realObject);
    proxy->request();
}

} // DesignPattern