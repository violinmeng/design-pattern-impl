#include "abstract_factory.hpp"
#include "base.hpp"// NOLINT
#include "bridge.hpp"
#include "builder.hpp"
#include "composite.hpp"
#include "decorator.hpp"
#include "facade.hpp"
#include "factory.hpp"
#include "flyweight.hpp"
#include "prototype.hpp"
#include "proxy.hpp"
#include "chain.hpp"
#include "command.hpp"
#include "iterator.hpp"
#include "mediator.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

namespace {

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
  const std::unique_ptr<DesignPattern::FurnitureFactory> vff =
    std::make_unique<DesignPattern::VictorianFurnitureFactory>();
  abstractFactoryClientCode(vff);
  std::cout << "Client: Testing the same client code with the second factory type:\n";
  const std::unique_ptr<DesignPattern::FurnitureFactory> mff =
    std::make_unique<DesignPattern::ModernFurnitureFactory>();
  abstractFactoryClientCode(mff);
}

void builderMain()
{
  const std::unique_ptr<DesignPattern::Director> director = std::make_unique<DesignPattern::Director>();
  builderClientCode(*director);
}

void prototypeMain()
{
  const std::unique_ptr<DesignPattern::PrototypeFactory> factory = std::make_unique<DesignPattern::PrototypeFactory>();
  prototypeClientCode(*factory);
}

void bridgeMain() { DesignPattern::bridgeClientCode(); }

void compositeMain() { DesignPattern::compositeClientCode(); }

void decoratorMain() { DesignPattern::decoratorClientCode(); }

void facadeMain() { DesignPattern::facadeClientCode(); }

void flyweightMain() { DesignPattern::flyweightClientCode(); }

void proxyMain() { DesignPattern::proxyClientCode(); }

void chainMain() { DesignPattern::chainClientCode(); }

void commandMain() { DesignPattern::commandClientCode(); }

void iteratorMain() { DesignPattern::iteratorClientCode(); }

void mediatorMain() { DesignPattern::mediatorClientCode(); }

}// namespace

int main()
{
  try {
    // code here
    // factoryMain();
    // builderMain();
    // prototypeMain();
    // bridgeMain();
    // abstractFactoryMain();
    // compositeMain();
    // decoratorMain();
    // facadeMain();
    // flyweightMain();
    // proxyMain();
    // chainMain();
    // commandMain();
    // iteratorMain();
    mediatorMain();
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
