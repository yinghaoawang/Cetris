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

		setPiecePositions(newPositions);

		return true;
	}

	void Tetromino::setPiecePositions(const std::vector<Piece>& positions) {
		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			p.localPosition.x = positions[pi].localPosition.x;
			p.localPosition.y = positions[pi].localPosition.y;
		}
	}

	void Tetromino::setPiecePositions(const std::vector<sf::Vector2f>& positions) {
		for (int pi = 0; pi < pieces.size(); pi++) {
			Tetromino::Piece& p = pieces[pi];
			p.localPosition.x = positions[pi].x;
			p.localPosition.y = positions[pi].y;
		}
	}

	sf::Vector2f Tetromino::Piece::getRoundedWorldPosition() {
		return sf::Vector2f(round(tetromino.position.x) + round(localPosition.x), round(tetromino.position.y) + round(localPosition.y));
	}

	bool Tetromino::rotateClockwise() {
		return rotate(90 * (M_PI / 180));
	}

	bool Tetromino::rotateCounterClockwise() {
		return rotate(-90 * (M_PI / 180));
	}
}