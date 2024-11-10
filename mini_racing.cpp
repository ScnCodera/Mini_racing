#include <SFML/Graphics.hpp>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Car {
public:
    sf::RectangleShape shape; 
    float speed;
    float angle;

    Car(float posX, float posY) {
        shape.setSize(sf::Vector2f(50, 25));
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        shape.setPosition(posX, posY);
        shape.setFillColor(sf::Color::Red);
        speed = 0;
        angle = 0;
    }

    void update() {
        shape.move(std::cos(angle * 3.14159 / 180) * speed, std::sin(angle * 3.14159 / 180) * speed);
        shape.setRotation(angle);
    }

    void accelerate(float amount) {
        speed += amount;
        if (speed > 5) speed = 5;   
        if (speed < -3) speed = -3;  
    }

    void rotate(float amount) {
        angle += amount;
    }

    void applyFriction() {
        if (speed > 0) speed -= 0.05;
        if (speed < 0) speed += 0.05;
        if (std::abs(speed) < 0.05) speed = 0;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Racing Game");

    Car car(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) car.accelerate(0.1); 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) car.accelerate(-0.1); 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) car.rotate(-2); 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) car.rotate(2); 

        car.applyFriction();
        car.update();

        window.clear(sf::Color::Green); 
        window.draw(car.shape);
        window.display();
    }

    return 0;
}
