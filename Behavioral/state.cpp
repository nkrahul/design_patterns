#include <iostream>

class TrafficLightState {
    public:
    virtual void showLight() const = 0;
};

class RedLightSTate : public TrafficLightState {
    public:
    void showLight() const override {
        std::cout << "Traffic Light is Red.\n";
    }
};

class YellowLightSTate : public TrafficLightState {
    public:
    void showLight() const override {
        std::cout << "Traffic Light is Yellow.\n";
    }
};

class GreenLightSTate : public TrafficLightState {
    public:
    void showLight() const override {
        std::cout << "Traffic Light is Green.\n";
    }
};

class TrafficLight {
    private:
    TrafficLightState* state;

    public:
    void setState(TrafficLightState* state) {this->state = state;};
    void handleSignal() {state->showLight();}
};

int main() {
    TrafficLight trafficLight;
    RedLightSTate redState;
    YellowLightSTate yellowState;
    GreenLightSTate greenState;

    trafficLight.setState(&redState);
    trafficLight.handleSignal();
    trafficLight.setState(&yellowState);
    trafficLight.handleSignal();
    trafficLight.setState(&greenState);
    trafficLight.handleSignal();

    return 0;
}