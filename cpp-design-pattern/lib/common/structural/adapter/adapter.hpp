#pragma once

#include <string>
#include <algorithm>
#include <iostream>
// Adapter is a structural design pattern 
// that allows objects with incompatible interfaces to collaborate.
namespace DesignPattern {

// Object Adapter
class Target  {
public:
    virtual ~Target() = default;
    virtual std::string request() const {
        return "Target: The default target's behavior.";
    };
};

class Adaptee {
public:
    std::string specificRequest() const {
        return ".eetpadA eht fo roivaheb laicepsS";
    }
};

class Adapter : public Target {
private:
    Adaptee *adaptee;
public:
    Adapter(Adaptee *adaptee) : adaptee(adaptee) {}
    std::string request() const override {
        std::string to_reverse = this->adaptee->specificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

void adapterClientCode() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    auto target = std::make_unique<Target>();
    std::cout << target->request() << "\n\n";

    auto adaptee = std::make_unique<Adaptee>();
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->specificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    auto adapter = std::make_unique<Adapter>(adaptee.get());
    std::cout << adapter->request();
    std::cout << "\n";
};

// Class Adapter: Only can be implemented with languages that support multiple inheritance.
class MultiInheritAdapter : public Target, public Adaptee {
public:
    MultiInheritAdapter() {}
    std::string request() const override {
        std::string to_reverse = specificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void multiInheritAdapterClientCode(const Target *target) {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    auto target = std::make_unique<Target>();
    std::cout << target->request() << "\n\n";

    auto adaptee = std::make_unique<Adaptee>();
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->specificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    auto adapter = std::make_unique<MultiInheritAdapter>();
    std::cout << adapter->request();
    std::cout << "\n";
}

}