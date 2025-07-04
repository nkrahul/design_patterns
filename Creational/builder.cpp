#include <iostream>

class Pizza {
private:
    std::string dough;
    std::string sauce;
    std::string toppings;
public:
    ~Pizza() = default;
    void setDough(const std::string& d) { dough = d; }
    void setSauce(const std::string& s) { sauce = s; } 
    void setToppings(const std::string& t) { toppings = t; }
    void displayPizza() const {
        std::cout << "Pizza with dough: " << dough 
                  << ", sauce: " << sauce 
                  << ", toppings: " << toppings << std::endl;
    }
};

class PizzaBuilder {
    public:
    virtual ~PizzaBuilder() = default;
    virtual PizzaBuilder& buildDough() = 0;
    virtual PizzaBuilder& buildSauce() = 0;
    virtual PizzaBuilder& buildToppings() = 0;
    virtual Pizza getPizza() const = 0;
};

class MargheritaPizzaBuilder : public PizzaBuilder {
private:
    Pizza pizza;

public:
    PizzaBuilder& buildDough() override {
        pizza.setDough("Thin Crust");
        return *this;
    }

    PizzaBuilder& buildSauce() override {
        pizza.setSauce("Tomato Sauce");
        return *this;
    }

    PizzaBuilder& buildToppings() override {
        pizza.setToppings("Mozzarella Cheese, Basil");
        return *this;
    }

    Pizza getPizza() const override {
        return pizza;
    }
};

class PepperoniPizzaBuilder : public PizzaBuilder {
private:
    Pizza pizza;
public:
    PizzaBuilder& buildDough() override {
        pizza.setDough("Thick Crust");
        return *this;
    }
    PizzaBuilder& buildSauce() override {
        pizza.setSauce("Spicy Tomato Sauce");
        return *this;
    }   
    PizzaBuilder& buildToppings() override {
        pizza.setToppings("Pepperoni, Mozzarella Cheese");
        return *this;
    }
    Pizza getPizza() const override {
        return pizza;
    }
};

class PizzaDirector {
    private:
    PizzaBuilder& builder;
    public:
    PizzaDirector(PizzaBuilder& b) : builder(b) {}
    ~PizzaDirector() = default;
    Pizza makePizza() {
        return builder.buildDough()
                      .buildSauce()
                      .buildToppings()
                      .getPizza();
    }
};

int main() {
    std::cout << "Builder Pattern." << std::endl;
    MargheritaPizzaBuilder margheritaBuilder;
    PizzaDirector margheritaDirector(margheritaBuilder);
    Pizza margheritaPizza = margheritaDirector.makePizza();
    margheritaPizza.displayPizza();
    PepperoniPizzaBuilder pepperoniBuilder;
    PizzaDirector pepperoniDirector(pepperoniBuilder);
    Pizza pepperoniPizza = pepperoniDirector.makePizza();
    pepperoniPizza.displayPizza();
    return 0;
}