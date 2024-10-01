#pragma once

#include <string>
#include <memory>
#include <iostream>

namespace designPattern
{

class Product {

public:
    virtual ~Product() = default;
    virtual std::string operation() const = 0;
};

class ConcreteProductA : public Product {

public:
    std::string operation() const override {
        return "{Operating ConcreteProductA...}";
    }
    ~ConcreteProductA() {
        std::cout << "ConcreteProductA deallocating\n";
    }
};

class ConcreteProductB : public Product {

public:
    std::string operation() const override {
        return "{Operating ConcreteProductB...}";
    }
    ~ConcreteProductB() {
        std::cout << "ConcreteProductB deallocating\n";
    }
};

class Creator {

public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> factoryMethod() const = 0;

    std::string takeOperation() const {
        auto product = this->factoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->operation();
        return result;
    }
};

class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::unique_ptr<Product> product = std::make_unique<ConcreteProductA>();
        return product;
    }

    ~ConcreteCreatorA() {
        std::cout << "ConcreteCreatorA deallocating\n";
    }
};

class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        std::unique_ptr<Product> product = std::make_unique<ConcreteProductB>();
        return product;
    } 

    ~ConcreteCreatorB() {
        std::cout << "ConcreteCreatorB deallocating\n";
    }
};

std::unique_ptr<Creator> ClientCode(std::unique_ptr<Creator> creator) {
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator->takeOperation() << std::endl;
    return creator;
}

} // namespace designPattern


