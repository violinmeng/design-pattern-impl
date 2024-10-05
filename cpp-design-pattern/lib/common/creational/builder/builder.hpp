#pragma once

// Builder is a creational design pattern that lets you construct complex objects step by step.
// The pattern allows you to produce different types and representations of an object using the same construction code.

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace DesignPattern {

class BuilderProduct
{
public:
    std::vector<std::string> parts_;
    void listParts() const {
        std::cout << "Product parts:";
        for ( auto &part : parts_) {
            if (part == parts_.back())
            {
                std::cout << part;
            } else 
            {
                std::cout << part << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


class Builder {
public:
    virtual ~Builder() {}
    virtual void producePartA() const = 0;
    virtual void producePartB() const = 0;
    virtual void producePartC() const = 0;
};

class ConcreteBuilderA : public Builder
{
private:
    std::unique_ptr<BuilderProduct> product;
public:
    ConcreteBuilderA()
    {
        this->reset();
    }

    void reset()
    {
        this->product = std::make_unique<BuilderProduct>();
    }
    void producePartA() const override {
        this->product->parts_.push_back("PartA1");
    }
    void producePartB() const override {
        this->product->parts_.push_back("PartB1");
    }
    void producePartC() const override {
        this->product->parts_.push_back("PartC1");
    }
    std::unique_ptr<BuilderProduct> getProduct() {
        auto result = std::move(this->product);
        this->reset();
        return result;
    }
};

class Director {
private:
    std::unique_ptr<Builder> builder;

public:
    void setBuilder(std::unique_ptr<Builder> builder)
    {
        this->builder = std::move(builder);
    }
    Builder* getBuilder() {
        return this->builder.get();
    }
    void buildMinimalViableProduct()
    {
        this->builder->producePartA();
    }
    void buildFullFeatureProduct()
    {
        this->builder->producePartA();
        this->builder->producePartB();
        this->builder->producePartC();
    }
};

void builderClientCode(Director& director) {
    std::unique_ptr<Builder> builder = std::make_unique<ConcreteBuilderA>();
    director.setBuilder(std::move(builder));
    std::cout << "Standard basic product:\n";
    director.buildMinimalViableProduct();

    auto product = dynamic_cast<ConcreteBuilderA *>(director.getBuilder());
    auto result = product->getProduct();
    result.get()->listParts();

    std::cout << "Standard full featured product:\n"; 
    director.buildFullFeatureProduct();

    auto product1 = dynamic_cast<ConcreteBuilderA *>(director.getBuilder());
    auto result1 = product1->getProduct();
    result1.get()->listParts();

    std::cout << "Custom product:\n";
    std::unique_ptr<ConcreteBuilderA> builder1 = std::make_unique<ConcreteBuilderA>();
    builder1->producePartA();
    builder1->producePartC();
    auto product2=builder1.get()->getProduct();
    product2->listParts();
}
}