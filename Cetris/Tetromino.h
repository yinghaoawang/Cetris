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
			sf::Vector2f getRoundedWorldPosition();
		};

		static double tRound(double);

		
		std::vector<Piece> pieces;
		sf::Vector2f position;
		sf::Color color;
		Board& board; 

		Tetromino(Board& b, const sf::Color& c = sf::Color::White, sf::Vector2f p = sf::Vector2f(0, 0)) : board(b), color(c), position(p) {};
		bool rotateClockwise();
		bool rotateCounterClockwise();
		void setPiecePositions(const std::vector<Piece>&);
		void setPiecePositions(const std::vector<sf::Vector2f>&);

	protected:
		bool rotate(double);
	};
}
