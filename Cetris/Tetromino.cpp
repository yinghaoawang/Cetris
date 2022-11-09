#define _USE_MATH_DEFINES
#include "Tetromino.h"

namespace Cetris {
	bool Tetromino::rotateClockwise() {
		std::vector<sf::Vector2f> newPositions;
		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			float s = sin(90 * (M_PI / 180));
			float c = cos(90 * (M_PI / 180));
			sf::Vector2f newPosition(p.localPosition.x * c - p.localPosition.y * s, p.localPosition.x * s + p.localPosition.y * c);
			newPositions.push_back(newPosition);
		}

		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			if (p.localPosition.x != newPositions[pi].x) printf("%f %f\n", p.localPosition.x, newPositions[pi].x);
			p.localPosition.x = newPositions[pi].x;
			p.localPosition.y = newPositions[pi].y;
		}
		return true;
	}
}