#pragma once

#include <iostream>

// Template Method is a behavioral design pattern
// that allows you to define a skeleton of an algorithm in a base class
// and let subclasses override the steps
// without changing the overall algorithm’s structure.
namespace DesignPattern
{
class AbstractClass {
public:
    void templateMethod() const {
        this->baseOperation1();
        this->requiredOperations1();
        this->baseOperation2();
        this->hook();
        this->requiredOperation2();
        this->baseOperation3();
    }
protected:
    void baseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work\n";
    }
    void baseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations\n";
    }
    void baseOperation3() const {
        std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }
    virtual void requiredOperations1() const = 0;
    virtual void requiredOperation2() const = 0;
    virtual void hook() const {}
};
class ConcreteClass1 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1\n";
    }
    void requiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};
class ConcreteClass2 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1\n";
    }
    void requiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2\n";
    }
    void hook() const override {
        std::cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};
void templateMethodClientCode() {
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 class1{};
    class1.templateMethod();
    std::cout << "\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 class2{};
    class2.templateMethod();
}

} // namespace DesignPattern
