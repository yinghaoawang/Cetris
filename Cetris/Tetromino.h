#pragma once
#include <SFML/Graphics.hpp>

namespace Cetris {
	class Tetromino {
	public:
		class Piece {
		public:
			Tetromino& tetromino;

			Piece(const Tetromino&);
			sf::Vector2f localPosition;
		};

		Tetromino(sf::Color& color);
		std::vector<Piece> pieces;
		sf::Vector2f position;
		sf::Color color;
	};
}
