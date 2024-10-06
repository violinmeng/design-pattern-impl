#pragma once

#include <string>
#include <memory>
#include <iostream>

namespace DesignPattern {

class Implementation {
public:
    virtual ~Implementation() = default;
    virtual std::string operationImpl() = 0;
};

class ConcreteImplementationA : public Implementation {
public:
    std::string operationImpl() override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementation {
public:
    std::string operationImpl() override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

class Abstraction {
protected:
    Implementation* implementation;
public:
    Abstraction(Implementation* implementation) : implementation(implementation) {}
    virtual ~Abstraction() = default;
    virtual std::string operation() {
        return "Abstraction: Base operation with:\n" + implementation->operationImpl();
    }
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {}
    std::string operation() override {
        return "ExtendedAbstraction: Extended operation with:\n" + implementation->operationImpl();
    }
};

void bridgeClientCode() {

    std::unique_ptr<Implementation> implementation = std::make_unique<ConcreteImplementationA>();
    std::unique_ptr<Abstraction> abstraction = std::make_unique<Abstraction>(implementation.get());
    std::cout << abstraction->operation() << '\n';

    implementation = std::make_unique<ConcreteImplementationB>();
    abstraction = std::make_unique<ExtendedAbstraction>(implementation.get());
    std::cout << abstraction->operation() << '\n';
}

}