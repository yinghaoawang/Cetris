#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

namespace Cetris {
	class Tetromino;

	class Board {
	public:
		static const int WIDTH = 10;
		static const int HEIGHT = 20;
		sf::Vector2f position{ 50., 20.};

		Board();
		void render(sf::RenderWindow&);
		void tick();
		

		class Tile {
		public:
			static const int WIDTH = 25;
			static const int HEIGHT = 25;

			Tile(sf::Color&);
			sf::Color color;
		};

		std::vector<std::vector<Tile*>> tiles{ HEIGHT, std::vector<Tile*>(WIDTH, nullptr) };
		std::vector<Tetromino> tetrominos;
	};
}
