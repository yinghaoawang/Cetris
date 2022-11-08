#include "Runner.h"

using namespace Cetris;

Runner::Runner() {
	init();
}

void Runner::tick() {
	rectangle.move(sf::Vector2f(0, rectangle.getSize().y));
}

void Runner::render() {
	window.clear();
	board.render(window);
	window.draw(rectangle);
	window.display();
}

void Runner::init() {
	Board board();

	rectangle.setFillColor(sf::Color::Magenta);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(-1.f);
	rectangle.setPosition(sf::Vector2f(0, 0));
}

void Runner::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time deltaTime = clock.restart();

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
}
