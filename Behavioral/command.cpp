#include <iostream>

class Receiver {
    public:
    void performOperation() const {
        std::cout << "Receiver is performing operation.\n";
    }
};

class Command {
    public:
    Command() = default;
    ~Command() = default;
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
    private:
    Receiver& receiver;
    public:
    ConcreteCommand(Receiver& rec) : receiver(rec) {}
    void execute() override {
        std::cout << "Command executed.\n";
        receiver.performOperation();
    }
};

class Invoker {
    private:
    Command* command;

    public:
    void setCommand(Command* com) {
        command = com;
    }
    void executeCommand() {
        command->execute();
    }
};

int main() {
    Invoker invoker;
    Receiver receiver;
    ConcreteCommand command(receiver);
    invoker.setCommand(&command);
    invoker.executeCommand();
    return 0;
}