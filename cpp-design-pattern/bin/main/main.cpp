#include "base.hpp" // NOLINT
#include "factory.hpp"
#include "abstract_factory.hpp"
#include "builder.hpp"
#include "prototype.hpp"
#include "bridge.hpp"

#include <iostream>
#include <exception>
#include <memory>
#include <utility>

using namespace std;

void factoryMain()
{
  std::cout << "Hello, world!\n";
  std::cout << "App: Launched with the ConcreteCreator1.\n";
  std::unique_ptr<DesignPattern::Creator> creator = std::make_unique<DesignPattern::ConcreteCreatorA>();
  ClientCode(std::move(creator));
  std::cout << '\n';
  std::cout << "App: Launched with the ConcreteCreator2.\n";
  std::unique_ptr<DesignPattern::Creator> creator1 = std::make_unique<DesignPattern::ConcreteCreatorB>();
  ClientCode(std::move(creator1));
}

void abstractFactoryMain()
{
  std::cout << "Client: Testing client code with the first factory type:\n";
  const std::unique_ptr<DesignPattern::FurnitureFactory> vff = std::make_unique<DesignPattern::VictorianFurnitureFactory>();
  abstractFactoryClientCode(vff);
  std::cout << "Client: Testing the same client code with the second factory type:\n";
  const std::unique_ptr<DesignPattern::FurnitureFactory> mff = std::make_unique<DesignPattern::ModernFurnitureFactory>();
  abstractFactoryClientCode(mff);
}

void builderMain() {
  const std::unique_ptr<DesignPattern::Director> director = std::make_unique<DesignPattern::Director>();
  builderClientCode(*director);
}

void prototypeMain() {
  const std::unique_ptr<DesignPattern::PrototypeFactory> factory = std::make_unique<DesignPattern::PrototypeFactory>();
  prototypeClientCode(*factory);
}

void bridgeMain() {
  DesignPattern::bridgeClientCode();
}

int main()
{
  try {
    // code here
    // factoryMain();
    // builderMain();
    // prototypeMain();
    bridgeMain();
    // abstractFactoryMain();
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}

