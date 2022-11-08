#pragma once
#include <SFML/Graphics.hpp>
#include "Pointf.h"

namespace Cetris {
	class Tetromino {
	public:
		class Piece {
		public:
			Tetromino& tetromino;

			Piece(const Tetromino&);
			Pointf localPosition;
		};

		std::vector<Piece> pieces;
		Pointf position;
		sf::Color color;
	};
}
