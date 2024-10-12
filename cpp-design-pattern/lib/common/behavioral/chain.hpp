#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

// Chain of Responsibility is a behavioral design pattern
// that lets you pass requests along a chain of handlers.
// Upon receiving a request,
// each handler decides
// either to process the request or to pass it to the next handler in the chain.

namespace DesignPattern
{

class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual std::string handle(std::string request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler *nextHandler;
public:
    AbstractHandler(): nextHandler(nullptr) {}
    Handler* setNext(Handler* handler) override {
        this->nextHandler = handler;
        return handler;
    }
    std::string handle(std::string request) override {
        if (this->nextHandler) {
            return this->nextHandler->handle(request);
        }
        return {};
    }
};

class MonkeyHandler : public AbstractHandler {
public:
    std::string handle(std::string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        return AbstractHandler::handle(request);
    }
};

class SquirrelHandler : public AbstractHandler {
public:
    std::string handle(std::string request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        return AbstractHandler::handle(request);
    }
};

class DogHandler : public AbstractHandler {
public:
    std::string handle(std::string request) override {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        }
        return AbstractHandler::handle(request);
    }
};

void proceedHandlers(Handler* handler) {
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const auto &f : food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler->handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        } else {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}

void chainClientCode() {
    auto monkey = std::make_unique<MonkeyHandler>();
    auto squirrel = std::make_unique<SquirrelHandler>();
    auto dog = std::make_unique<DogHandler>();
    monkey->setNext(squirrel.get())->setNext(dog.get());

    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    proceedHandlers(monkey.get());
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    proceedHandlers(squirrel.get());
}

} // namespace DesignPattern
