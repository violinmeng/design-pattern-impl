#include "base.hpp" // NOLINT
#include "factory.hpp" // NOLINT

#include <iostream>
#include <exception>
#include <memory>
#include <utility>

using namespace std;
int main()
{
  try {
    // code here
    std::cout << "Hello, world!\n";
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    std::unique_ptr<designPattern::Creator> creator = std::make_unique<designPattern::ConcreteCreatorA>();
    ClientCode(std::move(creator));
    std::cout << '\n';
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    std::unique_ptr<designPattern::Creator> creator1 = std::make_unique<designPattern::ConcreteCreatorB>();
    ClientCode(std::move(creator1));
    return 0;

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}

