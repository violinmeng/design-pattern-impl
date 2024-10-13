#pragma once

#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <memory>

// Visitor is a behavioral design pattern
// that allows adding new behaviors to existing class hierarchy
// without altering any existing code.

namespace DesignPattern
{
class CVComponentA;
class CVComponentB;
class Visitor {
public:
    virtual void visitComponentA(const CVComponentA *element) const = 0;
    virtual void visitComponentB(const CVComponentB *element) const = 0;
};

class VComponent {
public:
    virtual ~VComponent() = default;
    virtual void accept(Visitor *visitor) const = 0;
};

class CVComponentA : public VComponent {
public:
    void accept(Visitor *visitor) const override {
        visitor->visitComponentA(this);
    }

    std::string operationA() const {
        return "A";
    }
};

class CVComponentB : public VComponent {
public:
    void accept(Visitor *visitor) const override {
        visitor->visitComponentB(this);
    }

    std::string operationB() const {
        return "B";
    }
};

class CVisitorA : public Visitor {
public:
    void visitComponentA(const CVComponentA *element) const {
        std::cout << element->operationA() << " + ConcreteVisitorA.\n";
    }
    void visitComponentB(const CVComponentB *element) const {
        std::cout << element->operationB() << " + ConcreteVisitorA.\n";
    }
};

class CVisitorB : public Visitor {
public:
    void visitComponentA(const CVComponentA *element) const {
        std::cout << element->operationA() << " + ConcreteVisitorB.\n";
    }
    void visitComponentB(const CVComponentB *element) const {
        std::cout << element->operationB() << " + ConcreteVisitorB.\n";
    }
};

void visitorClientCode() {
    std::array<std::unique_ptr<VComponent>, 2> components = {std::make_unique<CVComponentA>(), std::make_unique<CVComponentB>()};
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    auto visitor1 = std::make_unique<CVisitorA>();
    std::for_each(components.begin(), components.end(), [&visitor1](std::unique_ptr<VComponent>& component) {
        component->accept(visitor1.get());;
    });
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    auto visitor2 = std::make_unique<CVisitorB>();
    std::for_each(components.begin(), components.end(), [&visitor2](std::unique_ptr<VComponent>& component) {
        component->accept(visitor2.get());;
    });
}

} // namespace DesignPattern
