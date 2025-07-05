#include <iostream>

class Device {
protected:
    bool on;
    int volume;
    int channel;

public:
    Device() : on(false), volume(0), channel(0) {}
    Device(bool isOn, int vol, int chan) : on(isOn), volume(vol), channel(chan) {}
    virtual bool isOn() const = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int vol) = 0;
    virtual int getVolume() const = 0;
    virtual void setChannel(int chan) = 0;
    virtual int getChannel() const = 0;
    virtual ~Device() = default;
};

class TV : public Device {
public:
    TV() : Device(false, 10, 1) {}
    TV(bool isOn, int vol, int chan) : Device(isOn, vol, chan) {}

    bool isOn() const override {
        std::cout << "TV is " << (on ? "on" : "off") << std::endl;
        return on;
    }

    int getVolume() const override {
        std::cout << "TV volume: " << volume << std::endl;
        return volume;
    }

    int getChannel() const override {
        std::cout << "TV channel: " << channel << std::endl;
        return channel;
    }
    void turnOn() override {
        on = true;
        std::cout << "TV turned on." << std::endl;
    }
    void turnOff() override {
        on = false;
        std::cout << "TV turned off." << std::endl;
    }
    void setVolume(int vol) override {
        volume = vol;
        std::cout << "TV volume set to: " << volume << std::endl;
    }
    void setChannel(int chan) override {
        channel = chan;
        std::cout << "TV channel set to: " << channel << std::endl;
    }
    ~TV() override {
        std::cout << "TV object destroyed." << std::endl;
    }
};

class Radio : public Device {
public:
    Radio() : Device(false, 5, 101) {}
    Radio(bool isOn, int vol, int chan) : Device(isOn, vol, chan) {}

    bool isOn() const override {
        std::cout << "Radio is " << (on ? "on" : "off") << std::endl;
        return on;
    }

    int getVolume() const override {
        std::cout << "Radio volume: " << volume << std::endl;
        return volume;
    }

    int getChannel() const override {
        std::cout << "Radio station: " << channel << std::endl;
        return channel;
    }

    void turnOn() override {
        on = true;
        std::cout << "Radio turned on." << std::endl;
    }

    void turnOff() override {
        on = false;
        std::cout << "Radio turned off." << std::endl;
    }
    void setVolume(int vol) override {
        volume = vol;
        std::cout << "Radio volume set to: " << volume << std::endl;
    }
    void setChannel(int chan) override {
        channel = chan;
        std::cout << "Radio channel set to: " << channel << std::endl;
    }
};

class RemoteControlInterface {
protected:
    Device* device;

public:
    RemoteControlInterface(Device* dev) : device(dev) {}
    virtual ~RemoteControlInterface() = default;
    virtual void togglePower() = 0;
    virtual void volumeUp() = 0;
    virtual void volumeDown() = 0;
    virtual void channelUp() = 0;
    virtual void channelDown() = 0;
};

class RemoteControl : public RemoteControlInterface {
public:
    RemoteControl(Device* dev) : RemoteControlInterface(dev) {}
    ~RemoteControl() override = default;
    void togglePower() override {
        if (device->isOn()) {
            device->turnOff();
        } else {
            device->turnOn();
        }
    }
    void volumeUp() override {
        if (device->isOn()) {
            device->setVolume(device->getVolume() + 1);
            device->getVolume();
        } else {
            std::cout << "Device is off. Cannot change volume." << std::endl;
        }
    }
    void volumeDown() override {
        if (device->isOn()) {
            if (device->getVolume() > 0) {
                device->setVolume(device->getVolume() - 1);
                device->getVolume();
            } else {
                std::cout << "Volume is already at minimum." << std::endl;
            }
        } else {
            std::cout << "Device is off. Cannot change volume." << std::endl;
        }
    }
    void channelUp() override {
        if (device->isOn()) {
            device->setChannel(device->getChannel() + 1);
            device->getChannel();
        } else {
            std::cout << "Device is off. Cannot change channel." << std::endl;
        }
    }
    void channelDown() override {
        if (device->isOn()) {
            if (device->getChannel() > 0) {
                device->setChannel(device->getChannel() - 1);
                device->getChannel();
            } else {
                std::cout << "Channel is already at minimum." << std::endl;
            }
        } else {
            std::cout << "Device is off. Cannot change channel." << std::endl;
        }
    }
};

class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(Device* dev) : RemoteControl(dev) {}

    void mute() {
        if (device->isOn()) {
            device->setVolume(0);
            std::cout << "Device muted." << std::endl;
        } else {
            std::cout << "Device is off. Cannot mute." << std::endl;
        }
    }
};

int main() {
    TV tv;
    Radio radio;

    RemoteControl tvRemote(&tv);
    RemoteControl radioRemote(&radio);

    std::cout << "Using TV remote:" << std::endl;
    tvRemote.togglePower();
    tvRemote.volumeUp();
    tvRemote.channelUp();
    tvRemote.volumeDown();
    tvRemote.channelDown();

    std::cout << "\nUsing Radio remote:" << std::endl;
    radioRemote.togglePower();
    radioRemote.volumeUp();
    radioRemote.channelUp();
    radioRemote.volumeDown();
    radioRemote.channelDown();

    return 0;
}