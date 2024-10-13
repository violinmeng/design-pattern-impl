#pragma once

// State is a behavioral design pattern
// that lets an object alter its behavior when its internal state changes.
// It appears as if the object changed its class.

#include <memory>
#include <iostream>
#include <utility>
#include <typeinfo>

namespace DesignPattern
{

class Context;
class State {
protected:
    Context* context;
public:
    virtual ~State() = default;
    void setContext(Context *ctx) {
        context = ctx;
    }
    virtual void handle1() = 0;
    virtual void handle2() = 0;
};

class Context {
private:
    std::unique_ptr<State> state;
public:
    Context(std::unique_ptr<State>&& state) : state(nullptr) {
        transitionTo(std::move(state));
    }
    void transitionTo(std::unique_ptr<State>&& state) {
        if (state.get()) {
            auto& refState = *state.get();
            std::cout << "Context: Transition to " << typeid(refState).name() << ".\n";
        }
        this->state = std::move(state);
        if (this->state) {
            this->state->setContext(this);
        }
    }
    void request1() {
        this->state->handle1();
    }
    void request2() {
        this->state->handle2();
    }
};

class StateA : public State {
public:
    void handle1() override;
    void handle2() override {
        std::cout << "StateA handles request2.\n";
    }
};

class StateB : public State {
public:
    void handle1() override {
        std::cout << "StateB handles request1.\n";
    }
    void handle2() override {
        std::cout << "StateB handles request2.\n";
        std::cout << "StateB wants to change the state of the context.\n";
        this->context->transitionTo(std::make_unique<StateA>());
    }
};

void StateA::handle1() {
    std::cout << "StateA handles request1.\n";
    std::cout << "StateA wants to change the state of the context.\n";

    this->context->transitionTo(std::make_unique<StateB>());
}

void stateClientCode() {
    auto stateA = std::make_unique<StateA>();
    auto ctx = std::make_unique<Context>(std::move(stateA));
    ctx->request1();
    ctx->request2();
}

} // namespace DesignPattern
