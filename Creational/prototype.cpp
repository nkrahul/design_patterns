#include <iostream>
#include <memory>

class Shape {
    public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
};

class Circle : public Shape {
    private:
    double radius;

    public:
    Circle(double radius = 0.0) : radius(radius) {
        std::cout << "Circle constructor called" << std::endl;
    }
    Circle(const Circle& circle) : radius(circle.radius) {
        std::cout << "Circle copy constructor called" << std::endl;
    }
    ~Circle() = default;
    Shape* clone() const override {
        return new Circle(*this);
    }
    void draw() const override {
        std::cout << "Drawing Circle with radius: " << radius << std::endl;
    };
};

class Square : public Shape {
    private:
    double side;

    public:
    Square(double side = 0.0) : side(side) {
        std::cout << "Square constructor called" << std::endl;
    };
    Square(const Square& square) : side(square.side) {
        std::cout << "Square copy constructor called" << std::endl;
    }
    ~Square() = default;
    Shape* clone() const override {
        return new Square(*this);
    }
    void draw() const override {
        std::cout << "Drawing Square with side: " << side << std::endl;
    };
};

int main() {
    std::cout << "Prototype pattern" << std::endl;
    std::shared_ptr<Shape> circlePrototype {std::make_shared<Circle>(5.0)};
    std::shared_ptr<Shape> squarePrototype {std::make_shared<Square>(4.0)};

    std::cout << "Cloning Circle prototype" << std::endl;
    std::unique_ptr<Shape> circle1 {circlePrototype->clone()};
    circle1->draw();
    std::unique_ptr<Shape> circle2 {circlePrototype->clone()};
    circle2->draw();

    std::cout << "Cloning Square prototype" << std::endl;
    std::unique_ptr<Shape> square1 {squarePrototype->clone()};
    square1->draw();
    std::unique_ptr<Shape> square2 {squarePrototype->clone()};
    square2->draw();

    return 0;
}