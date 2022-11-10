#include "Board.h"

using namespace Cetris;

Board::Tile::Tile(sf::Color& color) {
	this->color = color;
}

Board::Board() {
	tiles[3][2] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	Tetromino t(*this, sf::Color::Green, sf::Vector2f(5, 10));
	t.pieces.push_back(Tetromino::Piece(t, sf::Vector2f(-1., 0.)));
	t.pieces.push_back(Tetromino::Piece(t, sf::Vector2f(0., 0.)));
	t.pieces.push_back(Tetromino::Piece(t, sf::Vector2f(1., 0.)));
	t.pieces.push_back(Tetromino::Piece(t, sf::Vector2f(0., -1.)));
	tetrominos.push_back(t);
}

void Board::tick() {
	for (int ti = 0; ti < tetrominos.size(); ti++) {
		Tetromino& t = tetrominos[ti];
		t.position.y++;
		t.rotateCounterClockwise();
	}
}

void Board::render(sf::RenderWindow& window) {
	// draw border
	sf::Vertex border[] = {
		sf::Vertex(sf::Vector2f(position.x, position.y)),
		sf::Vertex(sf::Vector2f(position.x, position.y + HEIGHT * Tile::HEIGHT)),
		sf::Vertex(sf::Vector2f(position.x + WIDTH * Tile::WIDTH, position.y + HEIGHT * Tile::HEIGHT)),
		sf::Vertex(sf::Vector2f(position.x + WIDTH * Tile::WIDTH, position.y))
	};
	window.draw(border, 4, sf::LineStrip);

	// draw tiles
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] == nullptr) continue;
			sf::RectangleShape rect(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
			rect.setPosition(sf::Vector2f(position.x + j * Tile::WIDTH, position.y + i * Tile::HEIGHT));
			rect.setFillColor(tiles[i][j]->color);
			window.draw(rect);
		}
	}

	// draw tetrominos
	for (int ti = 0; ti < tetrominos.size(); ti++) {
		Tetromino& tetromino = tetrominos[ti];
		sf::Vector2f tRoundedPosition(round(tetromino.position.x), round(tetromino.position.y));
		for (int pi = 0; pi < tetromino.pieces.size(); pi++) {
			Tetromino::Piece& piece = tetromino.pieces[pi];
			sf::RectangleShape rect(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
			sf::Vector2f pRoundedPosition(round(piece.localPosition.x), round(piece.localPosition.y));
			rect.setPosition(sf::Vector2f(position.x + (tRoundedPosition.x + pRoundedPosition.x) * Tile::WIDTH,
										  position.y + (tRoundedPosition.y + pRoundedPosition.y) * Tile::HEIGHT));
			rect.setFillColor(tetromino.color);
			window.draw(rect);
		}
	}
}
