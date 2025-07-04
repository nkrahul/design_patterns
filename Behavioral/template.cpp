#include <iostream>
#include <memory>

class VehicleTemplate {
    public:
    void buildVehicle() const {
        assembleBody();
        addEngine();
        addWheels();
        std::cout << "Vehicle assembly complete." << std::endl;
    }

    virtual void assembleBody() const = 0;
    virtual void addEngine() const = 0;
    virtual void addWheels() const = 0;
};

class Car : public VehicleTemplate {
    public:
    void assembleBody() const override {
        std::cout << "Assembling car body." << std::endl;
    }

    void addEngine() const override {
        std::cout << "Adding car engine." << std::endl;
    }

    void addWheels() const override {
        std::cout << "Adding car wheels." << std::endl;
    }
};

class Motorcycle : public VehicleTemplate {
    public:
    void assembleBody() const override {
        std::cout << "Assembling motorcycle body." << std::endl;
    }

    void addEngine() const override {
        std::cout << "Adding motorcycle engine." << std::endl;
    }

    void addWheels() const override {
        std::cout << "Adding motorcycle wheels." << std::endl;
    }
};

int main() {
    std::unique_ptr<VehicleTemplate> car = std::make_unique<Car>();
    std::unique_ptr<VehicleTemplate> motorcycle = std::make_unique<Motorcycle>();

    car->buildVehicle();
    motorcycle->buildVehicle();

    return 0;
}