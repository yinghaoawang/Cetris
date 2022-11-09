#include "Runner.h"

using namespace Cetris;

Runner::Runner() {
	init();
}

void Runner::tick() {
	board.tick();
}

void Runner::render() {
	window.clear();
	board.render(window);
	window.display();
}

void Runner::init() {
	Board board();
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
