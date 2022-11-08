#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

namespace Cetris {
    class Runner {
    public:
		Runner();
        void run();

    private:
		Board board;

		void tick();
		void render();
		void init();

		int fps = 60;
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time timePerFrame = sf::milliseconds(1000.f / fps);
		sf::Time timeSinceLastTick = sf::Time::Zero;
		sf::Time timePerTick = sf::milliseconds(1000.f);

		sf::RenderWindow window{ sf::VideoMode(600, 600), "SFML works!" };
		sf::RectangleShape rectangle{ sf::Vector2f(20, 20) };
    };
}
