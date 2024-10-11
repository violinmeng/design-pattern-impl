#pragma once

#include <string>
#include <iostream>
#include <utility>

namespace DesignPattern {

class Subsystem1 {

public:
    std::string operation1() const {
        return "Subsystem1: ready!\n";
    }
    std::string operationN() const {
        return "Subsystem1: go!\n";
    }
};

class Subsystem2 {

public:
    std::string operation1() const {
        return "Subsystem2: ready!\n";
    }
    std::string operationZ() const {
        return "Subsystem2: go!\n";
    }
};

class Facade {
protected:
    std::unique_ptr<Subsystem1> system1;
    std::unique_ptr<Subsystem2> system2;

public:
    Facade(std::unique_ptr<Subsystem1> sys1 = std::make_unique<Subsystem1>(), std::unique_ptr<Subsystem2> sys2 = std::make_unique<Subsystem2>()) 
        : system1(std::move(sys1)), system2(std::move(sys2)) {}
    std::string operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->system1->operation1();
        result += this->system2->operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->system1->operationN();
        result += this->system2->operationZ();
        return result;
    }
};

void facadeClientCode() {
    auto sys1 = std::make_unique<Subsystem1>();
    auto sys2 = std::make_unique<Subsystem2>();
    auto facade = std::make_unique<Facade>(std::move(sys1), std::move(sys2));
    std::cout << facade->operation();
}

}