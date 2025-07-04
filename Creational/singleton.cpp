#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
    private:
    static std::mutex mtx;
    
    Singleton() {
        std::cout << "Singleton created" << std::endl;
    };
    ~Singleton() {
        std::cout << "Singleton destroyed" << std::endl;
    };

    public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};

std::mutex Singleton::mtx;

int main() {
    Singleton& singleton {Singleton::getInstance()};
    Singleton& anotherSingleton {Singleton::getInstance()};
    if (&singleton == &anotherSingleton) {
        std::cout << "Both references point to the same instance." << std::endl;
    } else {
        std::cout << "Different instances!" << std::endl;
    }

    return 0;
}