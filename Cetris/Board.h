#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

namespace Cetris {
	class Board {
	public:
		static const int WIDTH = 10;
		static const int HEIGHT = 20;

		Board();
		void draw();
		

		class Tile {
		public:
			Tile();
			sf::Color color;
		};

		std::vector<std::vector<Tile*>> tiles{ HEIGHT, std::vector<Tile*>(WIDTH, nullptr) };
		std::vector<Tetromino> tetrominos();
	};
}
