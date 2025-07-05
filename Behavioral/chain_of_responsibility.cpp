#include <iostream>

class Request {
    private:
    std::string message;
    public:
    Request(const std::string& msg) : message(msg) {}
    std::string getMessage() const {
        return message;
    }
};

class Support {
    protected:
    Support* nextLevelSupport;
    public:
    Support() = default;
    virtual ~Support() = default;
    Support* setNextLevelSupport(Support* nextSupport) {
        nextLevelSupport = nextSupport;
        return nextLevelSupport;
    }
    virtual void handleRequest(Request& request) const = 0;
};

class LevelOneSupport : public Support {
    public:
    LevelOneSupport() = default;
    ~LevelOneSupport() = default;
    void handleRequest(Request& request) const override {
        if(request.getMessage() == "Normal") {
            std::cout << "Handled by LevelOneSupport\n";
        } else if(nextLevelSupport) {
            nextLevelSupport->handleRequest(request);
        }
    }
};

class LevelTwoSupport : public Support {
    public:
    LevelTwoSupport() = default;
    ~LevelTwoSupport() = default;
    void handleRequest(Request& request) const override {
        if(request.getMessage() == "High") {
            std::cout << "Handled by LevelTwoSupport\n";
        } else if(nextLevelSupport) {
            nextLevelSupport->handleRequest(request);
        }
    }
};

class LevelThreeSupport : public Support {
    public:
    LevelThreeSupport() = default;
    ~LevelThreeSupport() = default;
    void handleRequest(Request& request) const override {
        if(request.getMessage() == "Critical") {
            std::cout << "Handled by LevelThreeSupport\n";
        } else if(nextLevelSupport) {
            nextLevelSupport->handleRequest(request);
        }
    }
};

int main() {
    Request request("Critical");
    Request highRequest("High");

    LevelOneSupport levelOneSupport;
    LevelTwoSupport levelTwoSupport;
    LevelThreeSupport levelThreeSupport;

    levelOneSupport.setNextLevelSupport(&levelTwoSupport)->setNextLevelSupport(&levelThreeSupport);

    levelOneSupport.handleRequest(request);
    levelOneSupport.handleRequest(highRequest);

    return 0;
}