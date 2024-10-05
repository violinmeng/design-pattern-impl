#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <map>

// Prototype is a creational design pattern 
// that lets you copy existing objects without making your code dependent on their classes.
namespace DesignPattern {

class Prototype
{
protected:
    std::string prototypeName;
    float prototypeField;
public:
    Prototype() = default;
    Prototype(std::string prototypeName): prototypeName(prototypeName) {}
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() = 0;
    virtual void method(float prototypeField) {
        this->prototypeField = prototypeField;
        std::cout << "Call Method from " << prototypeName << " with field : " << prototypeField << std::endl;
    }
};

class ConcretePrototype1 : public Prototype
{
private:
    float concretePrototypeField1;
public:
    ConcretePrototype1(std::string prototypeName, float concretePrototypeField1) 
        : Prototype(prototypeName), concretePrototypeField1(concretePrototypeField1) {}
    std::unique_ptr<Prototype> clone() override {
        std::unique_ptr<Prototype> result = std::make_unique<ConcretePrototype1>(*this);
        return result;
    }
};

class ConcretePrototype2 : public Prototype
{
private:
    float concretePrototypeField2;
public:
    ConcretePrototype2(std::string prototypeName, float concretePrototypeField2) 
        : Prototype(prototypeName), concretePrototypeField2(concretePrototypeField2) {}
    std::unique_ptr<Prototype> clone() override {
        std::unique_ptr<Prototype> result = std::make_unique<ConcretePrototype2>(*this);
        return result;
    }
};

enum class Type
{
    PROTOTYPE_1,
    PROTOTYPE_2
};

class PrototypeFactory
{
private:
    std::map<Type, std::unique_ptr<Prototype>> prototypes;
public:
    PrototypeFactory() {
        std::unique_ptr<Prototype> prototype1 = std::make_unique<ConcretePrototype1>("PROTOTYPE_1", 5.0f);
        prototypes[Type::PROTOTYPE_1] = std::move(prototype1);
        std::unique_ptr<Prototype> prototype2 = std::make_unique<ConcretePrototype2>("PROTOTYPE_2", 6.0f);
        prototypes[Type::PROTOTYPE_2] = std::move(prototype2);
    }
    std::unique_ptr<Prototype> createPrototype(Type type) {
        return prototypes[type]->clone();
    }
};

void prototypeClientCode(PrototypeFactory &prototype_factory) {
    std::cout << "Let's create a Prototype 1\n";

    auto prototype = prototype_factory.createPrototype(Type::PROTOTYPE_1);
    prototype->method(90);

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.createPrototype(Type::PROTOTYPE_2);
    prototype->method(10);
}

}