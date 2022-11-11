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
	window.setKeyRepeatEnabled(false);
}

void Runner::manageInput() {
	board.manageInput(event, window, timeSinceLastTick);
}

void Runner::resetTickTimer() {
	timeSinceLastTick = sf::Time::Zero;
}

void Runner::run() {
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else
				manageInput();
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
