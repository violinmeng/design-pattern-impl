#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

namespace DesignPattern {

class Component {
protected:
    Component *parent;
public:
    void setComponent(Component *component) {
        this->parent = component;
    }
    Component *getComponent() {
        return this->parent;
    }

    virtual ~Component() = default;
    virtual void add(Component *component) {}
    virtual void remove(Component *component) {}
    virtual bool isComposite() {
        return false;
    }
    virtual std::string operation() = 0;
};

class Leaf : public Component {
public:
    std::string operation() override {
        return "Leaf";
    }
};
class Composite : public Component {
private:
    std::vector<Component *> children;
public:
    void add(Component *component) override {
        this->children.push_back(component);
        component->setComponent(this);
    }
    void remove(Component *component) override {
        auto it = std::find(children.begin(), children.end(), component);
        if (it != children.end()) {
            children.erase(it);
            component->setComponent(nullptr);
        }
    }

    bool isComposite() override {
        return true;
    }

    std::string operation() override {
        std::string result;
        for (const auto &child : children) {
            if (child == children.back()) {
                result += child->operation();
                continue;
            }
            result += child->operation() + "+";
        }
        return "Branch(" + result + ")";
    }
};

void compositeClientCode() {
    auto simple = std::make_unique<Leaf>();
    std::cout << "Client: I've got a simple component:\n";
    std::cout << "RESULT: " << simple->operation();
    std::cout << "\n\n";

    auto tree = std::make_unique<Composite>();
    auto branch1 = std::make_unique<Composite>();

    auto leaf_1 = std::make_unique<Leaf>();
    auto leaf_2 = std::make_unique<Leaf>();
    auto leaf_3 = std::make_unique<Leaf>();
    branch1->add(leaf_1.get());
    branch1->add(leaf_2.get());

    auto branch2 =  std::make_unique<Composite>();
    branch2->add(leaf_3.get());
    tree->add(branch1.get());
    tree->add(branch2.get());
    std::cout << "Client: Now I've got a composite tree:\n";
    std::cout << "RESULT: " << tree->operation();
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    if (tree->isComposite()) {
        tree->add(simple.get());
    }
    std::cout << "RESULT: " << tree->operation();
    std::cout << "\n";
}

}