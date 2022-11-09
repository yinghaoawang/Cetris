#pragma once
#include <SFML/Graphics.hpp>

namespace Cetris {
	class Tetromino {
	public:
		class Piece {
		public:
			Tetromino& tetromino;
			sf::Vector2f localPosition;

			Piece(Tetromino& t, sf::Vector2f p) : tetromino(t), localPosition(p) {}
		};

		std::vector<Piece> pieces;
		sf::Vector2f position;
		sf::Color color;

		Tetromino(const sf::Color& c, sf::Vector2f p) : color(c), position(p) {}
	};
}
