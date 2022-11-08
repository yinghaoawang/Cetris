#include "Board.h"

using namespace Cetris;

Board::Tile::Tile(sf::Color& color) {
	this->color = color;
}

Board::Board() {
	tiles[3][2] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
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
			sf::Color& color = tiles[i][j]->color;
			sf::RectangleShape rect(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
			rect.setPosition(sf::Vector2f(position.x + j * Tile::HEIGHT, position.y + i * Tile::WIDTH));
			rect.setFillColor(color);
			window.draw(rect);
		}
	}
}
