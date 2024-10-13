#pragma once

#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

// Observer is a behavioral design pattern
// that lets you define a subscription mechanism to notify multiple objects
// about any events that happen to the object they’re observing.

namespace DesignPattern
{

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string &message) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

class ConcreteSubject : public ISubject {
public:
    virtual ~ConcreteSubject() {
        std::cout << "goodbye, I was the Subject.\n";
    }
    void attach(IObserver* observer) override {
        observers.push_back(observer);
    }
    void detach(IObserver* observer) override {
        observers.remove(observer);
    }
    void notify() override {
        std::cout << "There are " << observers.size() << " observers in the list.\n";
        std::for_each(observers.begin(), observers.end(), [this](IObserver* observer) {
            observer->update(this->message);
        });
    }

    void createMessage(std::string message = "Empty") {
        this->message = message;
        notify();
    }

    void someBizLogis() {
        this->message = "change message message";
        notify();
        std::cout << "I'm about to do some thing important\n";
    }
private:
    std::list<IObserver*> observers;
    std::string message;
};

class Observer : public IObserver {
private:
    ISubject& subject;
    static int staticNumber;
    int number;
    std::string message;
public:
    Observer(ISubject& subject) : subject(subject) {
        this->subject.attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::staticNumber << "\".\n";
        this->number = Observer::staticNumber;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number << "\".\n";
    }

    void update(const std::string& message) override {
        this->message = message;
        printInfo();
    }

    void removeFromList() {
        subject.detach(this);
        std::cout << "Observer \"" << number << "\" removed from the list.\n";
    }
    void printInfo() {
        std::cout << "Observer \"" << this->number << "\": a new message is available --> " << this->message << "\n";
    }
};

int Observer::staticNumber = 0;

void observerClientCode() {
    auto subject = std::make_unique<ConcreteSubject>();
    auto observer1 = std::make_unique<Observer>(*subject.get());
    auto observer2 = std::make_unique<Observer>(*subject.get());
    auto observer3 = std::make_unique<Observer>(*subject.get());

    subject->createMessage("Hello World! :D");
    observer3->removeFromList();

    subject->createMessage("The weather is hot today! :p");
    auto observer4 = std::make_unique<Observer>(*subject.get());

    observer2->removeFromList();
    auto observer5 = std::make_unique<Observer>(*subject.get());

    subject->createMessage("My new car is great! ;)");
    observer5->removeFromList();

    observer4->removeFromList();
    observer1->removeFromList();
}

} // namespace DesignPattern
