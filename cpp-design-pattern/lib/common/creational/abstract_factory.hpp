#pragma once

#include <iostream>
#include <memory>

// Abstract Factory is a creational design pattern 
// that lets you produce **families** of related objects without specifying their concrete classes.

namespace DesignPattern {

class Chair {
public:
    virtual ~Chair() = default;
    virtual int legs() = 0;
    virtual void sitOn() = 0;
};

class VictorianChair : public Chair {
public:
    int legs() override {
        return 4;
    }
    void sitOn() override {
        std::cout << "Sitting on victorian chair" << std::endl;
    }
};

class ModernChair : public Chair {
public:
    int legs() override {
        return 4;
    }
    void sitOn() override {
        std::cout << "Sitting on modern chair" << std::endl;
    }
};

class Table {
public:
    virtual ~Table() = default;
    virtual int legs() = 0;
    virtual void putOn() = 0;
};

class VictorianTable : public Table {
public:
    int legs() override {
        return 4;
    }
    void putOn() override {
        std::cout << "Putting on victorian table" << std::endl;
    }
};

class ModernTable : public Table {
public:
    int legs() override {
        return 4;
    }
    void putOn() override {
        std::cout << "Putting on modern table" << std::endl;
    }
};

class Sofa {
public:
    virtual ~Sofa() = default;
    virtual int legs() = 0;
    virtual void sitOn() = 0;
};

class VictorianSofa : public Sofa {
public:
    int legs() override {
        return 4;
    }
    void sitOn() override {
        std::cout << "Sitting on victorian sofa" << std::endl;
    }
};

class ModernSofa : public Sofa {
public:
    int legs() override {
        return 4;
    }
    void sitOn() override {
        std::cout << "Sitting on modern sofa" << std::endl;
    }
};

class FurnitureFactory {
public:
    virtual ~FurnitureFactory() = default;
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Table> createTable() const = 0;
    virtual std::unique_ptr<Sofa> createSofa() const = 0;
};


class VictorianFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<VictorianChair>();
    }
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<VictorianTable>();
    }
    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<VictorianSofa>();
    }
};
class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ModernTable>();
    }
    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ModernSofa>();
    }
};

void abstractFactoryClientCode(const std::unique_ptr<FurnitureFactory> &factory) {
    auto chair = factory->createChair();
    auto table = factory->createTable();
    auto sofa = factory->createSofa();
    chair->sitOn();
    table->putOn();
    sofa->sitOn();
}
}