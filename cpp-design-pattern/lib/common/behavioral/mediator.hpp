#pragma once

#include <string>
#include <iostream>
#include <memory>

namespace DesignPattern
{
class BaseComponent;
class Mediator {
public:
    virtual void notify(BaseComponent *sender, std::string event) const = 0;
};

class BaseComponent {
protected:
    Mediator *mediator;
public:
    BaseComponent(Mediator *mediator = nullptr) : mediator(mediator) {}
    void setMediator(Mediator *med) {
        mediator = med;
    }
};

class ComponentA : public BaseComponent {
public:
    void operation1() {
        std::cout << "ComponentA is doing 1.\n";
        this->mediator->notify(this, "1");
    }
    void operation2() {
        std::cout << "ComponentA is doing 2.\n";
        this->mediator->notify(this, "2");
    }
};

class ComponentB : public BaseComponent {
public:
    void operation3() {
        std::cout << "ComponentB is doing 3.\n";
        this->mediator->notify(this, "3");
    }
    void operation4() {
        std::cout << "ComponentB is doing 4.\n";
        this->mediator->notify(this, "4");
    }
};

class ConcreteMediator : public Mediator {
private:
    ComponentA* compa;
    ComponentB* compb;
public:
    ConcreteMediator(ComponentA *compa, ComponentB* compb) : compa(compa), compb(compb) {
        this->compa->setMediator(this);
        this->compb->setMediator(this);
    }
    void notify(BaseComponent* sender, std::string event) const override {
        if (event == "1") {
            std::cout << "Mediator reacts on 1 and triggers following operations:\n";
            this->compb->operation3();
        }
        if (event == "4") {
            std::cout << "Mediator reacts on 4 and triggers following operations:\n";
            this->compa->operation2();
            this->compb->operation3();
        }
    }
};

void mediatorClientCode() {
    auto c1 = std::make_unique<ComponentA>();
    auto c2 = std::make_unique<ComponentB>();
    auto mediator = std::make_unique<ConcreteMediator>(c1.get(), c2.get());
    std::cout << "Client triggers operation 1.\n";
    c1->operation1();
    std::cout << "\n";
    std::cout << "Client triggers operation 4.\n";
    c2->operation4();
}

} // namespace DesignPattern
