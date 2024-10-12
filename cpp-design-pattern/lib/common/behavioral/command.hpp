#pragma once

#include <string>
#include <iostream>
#include <memory>

namespace DesignPattern
{
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
};

class SimpleCommand : public Command {
private:
    std::string payLoad;
public:
    explicit SimpleCommand(std::string payLoad) : payLoad(payLoad) {}
    void execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << payLoad << ")\n";
    }
};

class Receiver {
public:
    void doSomething(const std::string &some) {
        std::cout << "Receiver: Working on (" << some << ".)\n";
    }
    void doSomethingElse(const std::string &some) {
        std::cout << "Receiver: Also working on (" << some << ".)\n";
    }
};

class ComplexCommand : public Command {
private:
    Receiver* receiver;
    std::string something;
    std::string somethingElse;
public:
    ComplexCommand(Receiver *receiver, std::string something, std::string somethingElse)
        : receiver(receiver), something(something), somethingElse(somethingElse) {}
    
    void execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver->doSomething(something);
        this->receiver->doSomethingElse(somethingElse);
    }
};

class Invoker {
private:
    std::unique_ptr<Command> onStart;
    std::unique_ptr<Command> onFinish;
public:
    void setOnStart(std::unique_ptr<Command> &&command) {
        this->onStart = std::move(command);
    }
    void setOnFinish(std::unique_ptr<Command> &&command) {
        this->onFinish = std::move(command);
    }
    void doSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->onStart) {
            this->onStart->execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->onFinish) {
            this->onFinish->execute();
        }
    }
};

void commandClientCode() {
    std::unique_ptr<Invoker> invoker = std::make_unique<Invoker>();
    std::unique_ptr<Command> simple = std::make_unique<SimpleCommand>("Say Hi!");
    invoker->setOnStart(std::move(simple));

    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();
    std::unique_ptr<Command> complex = std::make_unique<ComplexCommand>(receiver.get(), "Send email", "Save report");
    invoker->setOnFinish(std::move(complex));
    invoker->doSomethingImportant();
}

} // namespace DesignPattern
