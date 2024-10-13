#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <utility>
#include <iostream>

// Strategy is a behavioral design pattern
// that turns a set of behaviors into objects
// and makes them interchangeable inside original context object.

namespace DesignPattern
{

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

class StrategyContext {
private:
    std::unique_ptr<Strategy> strategy;
public:
    explicit StrategyContext(std::unique_ptr<Strategy>&& strategy = {}) : strategy(std::move(strategy)) {}
    void setStrategy(std::unique_ptr<Strategy>&& strategy) {
        this->strategy = std::move(strategy);
    }
    void doBizLogic() const {
        if (strategy) {
            std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            std::string result = strategy->doAlgorithm("aecbd");
            std::cout << result << "\n";
        } else {
            std::cout << "Context: Strategy isn't set\n";
        }
    }
};
class StrategyA : public Strategy {
public:
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));
        return result;
    }
};

class StrategyB : public Strategy {
public:
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());
        return result;
    }
};

void strategyClientCode() {
    StrategyContext context(std::make_unique<StrategyA>());
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doBizLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.setStrategy(std::make_unique<StrategyB>());
    context.doBizLogic();
}

} // namespace DesignPattern
