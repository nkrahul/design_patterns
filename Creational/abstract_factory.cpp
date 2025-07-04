#include <iostream>
#include <memory>

class Pizza {
    public:
    virtual void prepare() const = 0;
    virtual ~Pizza() = default;
};

class NewYorkStyleCheesePizza : public Pizza {
    public:
    void prepare() const override {
        std::cout << "Preparing New York Style Cheese Pizza" << std::endl;
    }
};

class NewYorkStylePepperoniPizza : public Pizza {
    public:
    void prepare() const override {
        std::cout << "Preparing New York Style Pepperoni Pizza" << std::endl;
    }
};

class ChicagoStyleCheesePizza : public Pizza {
    public:
    void prepare() const override {
        std::cout << "Preparing Chicago Style Cheese Pizza" << std::endl;
    }
};

class ChicagoStylePepperoniPizza : public Pizza {
    public:
    void prepare() const override {
        std::cout << "Preparing Chicago Style Pepperoni Pizza" << std::endl;
    }
};

class PizzaFactory {
    public:
    virtual Pizza* createCheesePizza() const = 0;
    virtual Pizza* createPepperoniPizza() const = 0;
    virtual ~PizzaFactory() = default;
};

class NewYorkStylePizzaFactory : public PizzaFactory {
    public:
    Pizza* createCheesePizza() const override {
        return new NewYorkStyleCheesePizza();
    }
    Pizza* createPepperoniPizza() const override {
        return new NewYorkStylePepperoniPizza();
    }
    ~NewYorkStylePizzaFactory() override = default;
};

class ChicagoStylePizzaFactory : public PizzaFactory {
    public:
    Pizza* createCheesePizza() const override {
        return new ChicagoStyleCheesePizza();
    }
    Pizza* createPepperoniPizza() const override {
        return new ChicagoStylePepperoniPizza();
    }
    ~ChicagoStylePizzaFactory() override = default;
};

class PizzaStore {
    private:
    PizzaFactory* factory;

    public:
    PizzaStore(PizzaFactory* factory) : factory(factory) {}
    Pizza* orderCheesePizza() {
        Pizza* pizza {factory->createCheesePizza()};
        pizza->prepare();
        return pizza;
    }

    Pizza* orderPepperoniPizza() {
        Pizza* pizza {factory->createPepperoniPizza()};
        pizza->prepare();
        return pizza;
    }

};

int main () {
    std::cout << "Abstract Factory Pattern Example" << std::endl;
    auto newYorkStylePizzaFactory {std::make_unique<NewYorkStylePizzaFactory>()};
    auto chicagoStylePizzaFactory {std::make_unique<ChicagoStylePizzaFactory>()};

    PizzaStore newYorkStore(newYorkStylePizzaFactory.get());
    PizzaStore chicagoStore(chicagoStylePizzaFactory.get());

    newYorkStore.orderCheesePizza();
    newYorkStore.orderPepperoniPizza();
    newYorkStore.orderPepperoniPizza();
    newYorkStore.orderCheesePizza();
    return 0;
}