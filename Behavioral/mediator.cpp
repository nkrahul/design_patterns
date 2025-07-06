#include <iostream>
#include <queue>

enum REQUEST {
    TAKEOFF = 1,
    LANDING
};

class Airplane {
    public:
    virtual void requestTakeOff() = 0;
    virtual void requestLanding() = 0;
    virtual std::string getName() const = 0;
    virtual ~Airplane() = default;
};

class PassengerPlane : public Airplane {
    private:
    std::string name;
    AirTrafficController* mediator;

    public:
    PassengerPlane(const std::string name, AirTrafficController* mediator)
        : name(name), mediator(mediator) {}

    void requestTakeOff() override {
        std::cout << "Requesting takeoff.\n";
        mediator->notify(this, TAKEOFF);
    }

    void requestLanding() override {
        std::cout << "Requesting Landing.\n";
        mediator->notify(this, LANDING);
    }
    std::string getName() const override {
        return name;
    }
};

class AirTrafficController {
    public:
    virtual void notify(Airplane* plane, REQUEST request) = 0;
};

class AirControlTower : public AirTrafficController {
    private:
    std::queue<std::pair<Airplane*, REQUEST>> requestQueue;

    public:
    void notify(Airplane* plane, REQUEST request) override {
        requestQueue.push({plane, request});
        
        auto req = requestQueue.front();
        requestQueue.pop();
        Airplane* flight = req.first;
        if(req.second == TAKEOFF) {
            std::cout << "Flight " << flight->getName() << " , please proceed for takeoff\n";
        }
        if(req.second == LANDING) {
            std::cout << "Flight " << flight->getName() << " , please proceed for landing\n";
        }
        auto q = requestQueue;
        while(!q.empty()) {
            auto p = q.front();
            q.pop();
            std::cout << "Flight " << p.first->getName() << " , please wait for request clearance\n";
        }
    }
};

int main() {
    AirControlTower mediator;

    PassengerPlane plane1("Indigo", &mediator);
    PassengerPlane plane2("Air India", &mediator);
    PassengerPlane plane3("Air Asia", &mediator);

    plane1.requestTakeOff();
    plane2.requestLanding();
    plane3.requestTakeOff();

    return 0;
}