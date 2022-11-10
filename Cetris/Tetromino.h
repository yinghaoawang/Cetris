#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

namespace Cetris {
	class Board;

	class Tetromino {
	public:
		class Piece {
		public:
			Tetromino& tetromino;
			sf::Vector2f localPosition;

			Piece(Tetromino& t, sf::Vector2f p) : tetromino(t), localPosition(p) {};
		};

		
		std::vector<Piece> pieces;
		sf::Vector2f position;
		sf::Color color;
		Board& board; 

		Tetromino(Board& b, const sf::Color& c, sf::Vector2f p) : board(b), color(c), position(p) {};
		bool rotateClockwise();
		bool rotateCounterClockwise();

	protected:
		bool rotate(float);
	};
}
