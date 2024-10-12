#pragma once

#include <string>
#include <ostream>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace DesignPattern
{

struct SharedState {
    std::string brand;
    std::string model;
    std::string color;
    SharedState(const std::string &brand, const std::string &model, const std::string &color)
        : brand(brand), model(model), color(color) {}
    friend std::ostream& operator<<(std::ostream& os, const SharedState &ss) {
        return os << "[" << ss.brand << " . "
                         << ss.model << " . "
                         << ss.color << ']';
    }
};

struct UniqueState {
    std::string owner;
    std::string plates;
    UniqueState(const std::string &owner, const std::string &plates)
        : owner(owner), plates(plates) {}
    
    friend std::ostream& operator<<(std::ostream& os, const UniqueState &us) {
        return os << "[" << us.owner << " . " << us.plates << "]";
    }
};

class Flyweight {
private:
    std::unique_ptr<SharedState> sharedState;
public:
    Flyweight(const SharedState *sharedState) : sharedState(std::make_unique<SharedState>(*sharedState)) {}
    Flyweight(const Flyweight &other) : sharedState(std::make_unique<SharedState>(*other.sharedState)) {}
    SharedState *getShareState() {
        return sharedState.get();
    }
    void operation(const UniqueState &us) const {
        std::cout << "Flyweight: Displaying shared (" << *this->sharedState.get() << ") and unique (" << us << ") state.\n";
    }
};

class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight> flyweight;
    std::string getKey(const SharedState &ss) const
    {
        return ss.brand + "_" + ss.model + "_" + ss.color;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState> share_states) {
        for (const SharedState &ss : share_states) {
            this->flyweight.insert(std::make_pair<std::string, Flyweight>(this->getKey(ss), Flyweight(&ss)));
        }
    }

    Flyweight getFlyweight(const SharedState &shared_state){
        std::string key = this->getKey(shared_state);
        if (this->flyweight.find(key) == this->flyweight.end()) {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->flyweight.insert(std::make_pair(key, Flyweight(&shared_state)));
        } else {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return this->flyweight.at(key);
    }
    void listFlyweights() const {
        size_t count = this->flyweight.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (std::pair<std::string, Flyweight> pair : this->flyweight) {
            std::cout << pair.first << "\n";
        }
    }
};

void AddCarToPoliceDatabase(
    FlyweightFactory &ff, const std::string &plates, const std::string &owner,
    const std::string &brand, const std::string &model, const std::string &color) {
    std::cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.getFlyweight({brand, model, color});
    flyweight.operation({owner, plates});
}

void flyweightClientCode() {
    auto factory = std::make_unique<FlyweightFactory>(FlyweightFactory{
        {"Chevrolet", "Camaro2018", "pink"},
        {"Mercedes Benz", "C300", "black"},
        {"Mercedes Benz", "C500", "red"},
        {"BMW", "M5", "red"},
        {"BMW", "X6", "white"}});
    factory->listFlyweights();

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");
    factory->listFlyweights();
}

} // namespace DesignPattern
