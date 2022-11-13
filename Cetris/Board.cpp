#include "Board.h"

using namespace Cetris;

Board::Tile::Tile(sf::Color& color) {
	this->color = color;
}

Board::Board() {
	tiles[19][5] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][0] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][1] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][2] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][3] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][4] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	tiles[19][9] = new Tile(const_cast<sf::Color&>(sf::Color::Blue));
	spawnNewTetromino();
}

void Board::solidifyTetromino() {
	std::vector<Tetromino::Piece>& pieces = tetrominoPtr->pieces;
	for (int pi = 0; pi < pieces.size(); pi++) {
		Tetromino::Piece& piece = pieces[pi];
		int x = piece.getRoundedWorldPosition().x;
		int y = piece.getRoundedWorldPosition().y;
		tiles[y][x] = new Tile(tetrominoPtr->color);
	}
	delete tetrominoPtr;
}

bool Board::isTetrominoKickable(std::vector<sf::Vector2f>* kickOffsetOut) {
	return false;
}

void Board::spawnNewTetromino() {
	tetrominoPtr = new Tetromino(*this, sf::Color::Green, sf::Vector2f(5, 10));
	tetrominoPtr->pieces.push_back(Tetromino::Piece(*tetrominoPtr, sf::Vector2f(-1., 0.)));
	tetrominoPtr->pieces.push_back(Tetromino::Piece(*tetrominoPtr, sf::Vector2f(0., 0.)));
	tetrominoPtr->pieces.push_back(Tetromino::Piece(*tetrominoPtr, sf::Vector2f(1., 0.)));
	tetrominoPtr->pieces.push_back(Tetromino::Piece(*tetrominoPtr, sf::Vector2f(0., -1.)));
}

void Board::handleTetrominoCollision() {
	solidifyTetromino();
	std::vector<int>* clearableLines = new std::vector<int>();;
	while (anyRowsClearable(clearableLines)) {
		sort(clearableLines->begin(), clearableLines->end());
		printf("%d\n", clearableLines->size());
		clearRows(*clearableLines);
		clearableLines->clear();
	}
	delete clearableLines;
	spawnNewTetromino();
}

bool Board::isTetrominoOutOfBounds(sf::Vector2i offset = sf::Vector2i(0, 0)) {
	std::vector<Tetromino::Piece>& pieces = tetrominoPtr->pieces;
	for (int pi = 0; pi < pieces.size(); pi++) {
		Tetromino::Piece& piece = pieces[pi];
		int x = piece.getRoundedWorldPosition().x + offset.x;
		int y = piece.getRoundedWorldPosition().y + offset.y;
		if (y > HEIGHT - 1 || x < 0 || x > WIDTH - 1) {
			printf("off the board!!\n");
			return true;
		}
	}
	return false;
}

bool Board::isTetrominoColliding(sf::Vector2i offset = sf::Vector2i(0, 0)) {
	if (isTetrominoOutOfBounds(offset)) {
		return true;
	}

	std::vector<Tetromino::Piece>& pieces = tetrominoPtr->pieces;
	for (int pi = 0; pi < pieces.size(); pi++) {
		Tetromino::Piece& piece = pieces[pi];
		int x = piece.getRoundedWorldPosition().x + offset.x;
		int y = piece.getRoundedWorldPosition().y + offset.y;
		printf("pos: %d %d\n", x, y);
		if (tiles[y][x] != nullptr) {
			printf("colliding on %d %d!!\n", x, y);
			return true;
		}
	}
	return false;
}

bool Board::anyRowsClearable(std::vector<int>* clearableRowsOut) {
	for (int i = 0; i < tiles.size(); i++) {
		bool rowIsClearable = true;
		for (int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] == nullptr) {
				rowIsClearable = false;
				break;
			}
		}

		if (rowIsClearable && clearableRowsOut != nullptr) clearableRowsOut->push_back(i);
	}
	if (clearableRowsOut != nullptr && clearableRowsOut->size() > 0) return true;
	return false;
}

void Board::clearRows(const std::vector<int>& rowsToClear) {
	for (int ri = rowsToClear.size() - 1; ri >= 0; ri--) {
		int row = rowsToClear[ri];
		for (int j = 0; j < tiles[row].size(); j++) {
			delete tiles[row][j];
		}
		tiles.erase(tiles.begin() + row);
	}
	while (tiles.size() < HEIGHT) tiles.insert(tiles.begin(), std::vector<Tile*>(WIDTH, nullptr)); // could be made more efficient
	printf("\n");
}

void Board::tick() {
	static sf::Vector2i oneDown(0, 1);
	if (isTetrominoColliding(oneDown)) {
		handleTetrominoCollision();
		return;
	}

	tetrominoPtr->position.y++;
}

void Board::manageInput(sf::Event& event, sf::RenderWindow& window, sf::Time& timeSinceLastTick) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q) {
			tetrominoPtr->rotateCounterClockwise();
			render(window);
		} else if (event.key.code == sf::Keyboard::E) {
			tetrominoPtr->rotateClockwise();
			render(window);
		} else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			tetrominoPtr->position.y++;
			timeSinceLastTick = sf::Time::Zero; // resets tick timer
			render(window);
		} else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
			tetrominoPtr->position.x--;
			render(window);
		} else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			tetrominoPtr->position.x++;
			render(window);
		} else if (event.key.code == sf::Keyboard::Space) {

		}
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

	// draw tetromino
	for (int pi = 0; pi < tetrominoPtr->pieces.size(); pi++) {
		Tetromino::Piece& piece = tetrominoPtr->pieces[pi];
		sf::RectangleShape rect(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
		rect.setPosition(sf::Vector2f(position.x + piece.getRoundedWorldPosition().x * Tile::WIDTH,
									  position.y + piece.getRoundedWorldPosition().y * Tile::HEIGHT));
		rect.setFillColor(tetrominoPtr->color);
		window.draw(rect);
	}
}
