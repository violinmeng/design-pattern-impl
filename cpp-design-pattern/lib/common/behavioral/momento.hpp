#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <memory>
#include "base.hpp"

namespace DesignPattern
{

class Momento {
public:
    virtual ~Momento() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDate() const = 0;
    virtual std::string getState() const = 0;
};

class CMomento : public Momento {
private:
    std::string date;
    std::string state;
public:
    explicit CMomento(std::string state) : state(state) {
        std::time_t now = std::time(NULL);
        std::tm * ptm = std::localtime(&now);
        char buffer[32];
        // Format: Mo, 15.06.2009 20:20:00
        if (std::strftime(buffer, sizeof buffer, "%a, %d.%m.%Y %H:%M:%S", ptm)) {
            date = buffer;
        } else {
            std::cout << "strftime failed";
        }
    }
    std::string getState() const override {
        return this->state;
    }
    std::string getName() const override {
        return this->date + " / (" + this->state.substr(0, 9) + "...)";
    }
    std::string getDate() const override {
        return this->date;
    }
};

class Originator {
private:
    std::string state;
    std::string genRandomString(int length = 10) {
        const std::string alphanum{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
        
        std::string randomString;
        DesignPatternBase::repeat(length, [&randomString, &alphanum]() {
            randomString += alphanum[std::rand() % alphanum.size()];
        });
        return randomString;
    }
public:
    Originator(std::string state) : state(state) {
        std::cout << "Originator: My initial state is: " << this->state << "\n";
    }
    void doSomething() {
        std::cout << "Originator: I'm doing something important.\n";
        this->state = this->genRandomString(30);
        std::cout << "Originator: and my state has changed to: " << this->state << "\n";
    }
    std::unique_ptr<Momento> save() {
        return std::make_unique<CMomento>(this->state);
    }
    void restore(Momento *momento) {
        this->state = momento->getState();
        std::cout << "Originator: My state has changed to: " << this->state << "\n";
    }
};

class Caretaker {
private:
    std::vector<std::unique_ptr<Momento>> momentos;
    Originator* originator;
public:
    Caretaker(Originator* originator) : originator(originator) {}
    void backup() {
        std::cout << "\nCaretaker: Saving Originator's state...\n";
        this->momentos.push_back(std::move(this->originator->save()));
    }
    void undo() {
        if (!this->momentos.size()) {
            return;
        }
        auto memento = std::move(this->momentos.back());
        this->momentos.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->getName() << "\n";
        try {
            this->originator->restore(memento.get());
        } catch (...) {
            this->undo();
        }
    }
    void showHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:\n";
        for (auto& memento : this->momentos) {
            std::cout << memento->getName() << "\n";
        }
    }
};

void momentoClientCode() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    auto originator = std::make_unique<Originator>("Super-duper-super-puper-super.");
    auto caretaker = std::make_unique<Caretaker>(originator.get());
    caretaker->backup();
    originator->doSomething();
    caretaker->backup();
    originator->doSomething();
    caretaker->backup();
    originator->doSomething();
    std::cout << "\n";
    caretaker->showHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->undo();
};

} // namespace DesignPattern
