#pragma once

#include <string>
#include <memory>
#include <iostream>

// Decorator is a structural pattern 
// that allows adding new behaviors to objects dynamically
// by placing them inside special wrapper objects, called decorators.
namespace DesignPattern {

class DecComponent {

public:
    virtual ~DecComponent() = default;
    virtual std::string operation() const = 0;
};

class ConcreteDecComponent : public DecComponent {

public:
    virtual std::string operation() const override {
        return "ConcreteDecComponent";
    }
};

class Decorator : public DecComponent {
protected:
    DecComponent *component;
public:
    Decorator(DecComponent *component): component(component) {}
    std::string operation() const override {
        return this->component->operation();
    }
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(DecComponent* component) : Decorator(component) {}
    std::string operation() const override {
        return "ConcreteDecoratorA(" + Decorator::operation() + ")";
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(DecComponent* component) : Decorator(component) {}
    std::string operation() const override {
        return "ConcreteDecoratorB(" + Decorator::operation() + ")";
    }
};

void decoratorClientCode() {
    auto simple = std::make_unique<ConcreteDecComponent>();
    std::cout << "Client: I've got a simple component:\n";
    std::cout << "RESUTL: " << simple->operation();
    std::cout << "\n\n";

    auto decorator1 = std::make_unique<ConcreteDecoratorA>(simple.get());
    auto decorator2 = std::make_unique<ConcreteDecoratorB>(decorator1.get());
    std::cout << "Client: Now I've got a decorated component:\n";
    std::cout << "RESUTL: " << decorator2->operation();
    std::cout << "\n";
}

}