#include <SFML/Graphics.hpp>

int fps = 60;
sf::Clock elapsedClock;
sf::Time timeSinceLastUpdate = sf::Time::Zero;
sf::Time timePerFrame = sf::milliseconds(1000.f / fps);
sf::Time timeSinceLastTick = sf::Time::Zero;
sf::Time timePerTick = sf::milliseconds(1000.f);

sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
sf::RectangleShape rectangle(sf::Vector2f(20, 20));

void tick() {
    rectangle.move(sf::Vector2f(0, rectangle.getSize().y));
}

void render() {
    window.clear();
    window.draw(rectangle);
    window.display();
}

int main() {
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(-1.f);
    rectangle.setPosition(sf::Vector2f(0, 0));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = elapsedClock.restart();

        timeSinceLastTick += deltaTime;
        while (timeSinceLastTick > timePerTick) {
            timeSinceLastTick -= timePerTick;
            tick();
        }

        timeSinceLastUpdate += deltaTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            render();
        }
    }

    return 0;
}