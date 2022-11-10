#define _USE_MATH_DEFINES
#include "Tetromino.h"

namespace Cetris {
	bool Tetromino::rotate(float rad) {
		std::vector<sf::Vector2f> newPositions;
		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			float s = sin(rad);
			float c = cos(rad);
			sf::Vector2f newPosition(p.localPosition.x * c - p.localPosition.y * s, p.localPosition.x * s + p.localPosition.y * c);
			newPositions.push_back(newPosition);
		}

		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			p.localPosition.x = newPositions[pi].x;
			p.localPosition.y = newPositions[pi].y;
		}
		return true;
	}

	bool Tetromino::rotateClockwise() {
		return rotate(90 * (M_PI / 180));
	}

	bool Tetromino::rotateCounterClockwise() {
		return rotate(-90 * (M_PI / 180));
	}
}