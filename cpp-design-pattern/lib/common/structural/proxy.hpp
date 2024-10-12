#pragma once

#include <iostream>
#include <memory>

// Proxy is a structural design pattern that lets you provide a substitute or placeholder for another object.
// A proxy controls access to the original object,
// allowing you to perform something either before or after the request gets through to the original object.

// Proxy VS Delegate
// They are quite similar conceptually but there are differences.
// In proxy pattern we use inheritance to provide a proxy object that appears in place of the original object.
// The delegation pattern is all about composition - the work is delegated to the composed object.

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
    std::unique_ptr<RealSubject> realSubject;

    bool checkAccess() const {
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }
    void logAccess() const { std::cout << "Proxy: Logging the time of request.\n"; }
public:
    Proxy(RealSubject *subject) : realSubject(std::make_unique<RealSubject>(*subject)) {}

    void request() const override {
        if (this->checkAccess()) {
            this->realSubject->request();
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
    auto proxy = std::make_unique<Proxy>(realObject.get());
    proxy->request();
}

} // DesignPattern