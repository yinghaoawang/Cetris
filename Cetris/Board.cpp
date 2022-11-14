#include "Board.h"

using namespace Cetris;

Board::Tile::Tile(sf::Color& color) {
	this->color = color;
}

Board::Board() {
	spawnNewTetromino();
}

void Board::solidifyTetromino() {
	std::vector<Tetromino::Piece>& pieces = tetrominoPtr->pieces;
	for (int pi = 0; pi < pieces.size(); pi++) {
		Tetromino::Piece& piece = pieces[pi];
		int x = piece.getRoundedWorldPosition().x;
		int y = piece.getRoundedWorldPosition().y;
		delete tiles[y][x];
		tiles[y][x] = new Tile(tetrominoPtr->color);
	}
	delete tetrominoPtr;
}

// Uses simple kick algorithm: check one to right and one to left
bool Board::isTetrominoKickable(Tetromino& tetromino, sf::Vector2i* kickOffsetOut) {
	// right
	if (!isTetrominoColliding(tetromino, sf::Vector2i(1, 0))) {
		kickOffsetOut->x = 1;
		kickOffsetOut->y = 0;
		return true;
	}

	// left
	if (!isTetrominoColliding(tetromino, sf::Vector2i(-1, 0))) {
		kickOffsetOut->x = -1;
		kickOffsetOut->y = 0;
		return true;
	}

	return false;
}

void Board::setTPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Magenta;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1., 0.)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0., 0.)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1., 0.)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0., -1.)));
}

void Board::setOPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Yellow;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-.5, -.5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-.5, .5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(.5, -.5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(.5, .5)));
}

void Board::setIPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Cyan;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1.5, -.5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-.5, -.5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(.5, -.5)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1.5, -.5)));
}

void Board::setJPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Blue;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1, -1)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1, 0)));
}

void Board::setLPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color(255, 128, 0);
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1, -1)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1, 0)));
}

void Board::setSPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Green;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, -1)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1, -1)));
}

void Board::setZPiece(Tetromino& tetromino) {
	tetromino.position = sf::Vector2f(5, 1);
	tetromino.color = sf::Color::Red;
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, -1)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(1, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(0, 0)));
	tetromino.pieces.push_back(Tetromino::Piece(tetromino, sf::Vector2f(-1, -1)));
}

void Board::spawnNewTetromino() {
	tetrominoPtr = new Tetromino(*this);
	std::vector<void(Board::*)(Tetromino&)> createFuncs = { &Board::setOPiece, &Board::setIPiece, &Board::setJPiece, &Board::setLPiece, &Board::setZPiece, &Board::setSPiece, &Board::setTPiece };
	void (Board::*createFunc)(Tetromino&);
	createFunc = createFuncs[std::rand() % createFuncs.size()];
	(this->*createFunc)(*tetrominoPtr);
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

bool Board::isTetrominoOutOfBounds(Tetromino& tetromino, sf::Vector2i offset = sf::Vector2i(0, 0)) {
	std::vector<Tetromino::Piece>& pieces = tetromino.pieces;
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

bool Board::isTetrominoColliding(Tetromino& tetromino, sf::Vector2i offset = sf::Vector2i(0, 0)) {
	if (isTetrominoOutOfBounds(tetromino, offset)) {
		return true;
	}

	std::vector<Tetromino::Piece>& pieces = tetromino.pieces;
	for (int pi = 0; pi < pieces.size(); pi++) {
		Tetromino::Piece& piece = pieces[pi];
		int x = piece.getRoundedWorldPosition().x + offset.x;
		int y = piece.getRoundedWorldPosition().y + offset.y;
		if (tiles[y][x] != nullptr) {
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
	if (isTetrominoColliding(*tetrominoPtr, oneDown)) {
		handleTetrominoCollision();
		return;
	}

	tetrominoPtr->position.y++;
}

void Board::manageInput(sf::Event& event, sf::RenderWindow& window, sf::Time& timeSinceLastTick) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Z) {
			Tetromino tmp(*tetrominoPtr);
			tmp.rotateCounterClockwise();
			if (!isTetrominoColliding(tmp)) {
				tetrominoPtr->rotateCounterClockwise();
				render(window);
			} else {
				sf::Vector2i kickOffsetOut;
				if (isTetrominoKickable(tmp, &kickOffsetOut)) {
					tmp.position.x += kickOffsetOut.x;
					tmp.position.y += kickOffsetOut.y;
					tetrominoPtr->setPiecePositions(tmp.pieces);
					tetrominoPtr->position.x = tmp.position.x;
					tetrominoPtr->position.y = tmp.position.y;
					render(window);
				}
			}
		} else if (event.key.code == sf::Keyboard::E || event.key.code == sf::Keyboard::X || event.key.code == sf::Keyboard::Up) {
			Tetromino tmp(*tetrominoPtr);
			tmp.rotateClockwise();
			if (!isTetrominoColliding(tmp)) {
				tetrominoPtr->rotateClockwise();
				render(window);
			} else {

			}
		} else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			if (!isTetrominoColliding(*tetrominoPtr, sf::Vector2i(0, 1))) {
				tetrominoPtr->position.y++;
				timeSinceLastTick = sf::Time::Zero; // resets tick timer
				render(window);
			}
		} else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
			if (!isTetrominoColliding(*tetrominoPtr, sf::Vector2i(-1, 0))) {
				tetrominoPtr->position.x--;
				render(window);
			}
		} else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			if (!isTetrominoColliding(*tetrominoPtr, sf::Vector2i(1, 0))) {
				tetrominoPtr->position.x++;
				render(window);
			}
		} else if (event.key.code == sf::Keyboard::Space) {
			while (!isTetrominoColliding(*tetrominoPtr, sf::Vector2i(0, 1))) {
				tetrominoPtr->position.y++;
			}
			handleTetrominoCollision();
			render(window);
		}
	}
}

void Board::render(sf::RenderWindow& window) {
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

	// draw border
	sf::Vertex border[] = {
		sf::Vertex(sf::Vector2f(position.x, position.y)),
		sf::Vertex(sf::Vector2f(position.x, position.y + HEIGHT * Tile::HEIGHT)),
		sf::Vertex(sf::Vector2f(position.x + WIDTH * Tile::WIDTH, position.y + HEIGHT * Tile::HEIGHT)),
		sf::Vertex(sf::Vector2f(position.x + WIDTH * Tile::WIDTH, position.y))
	};
	window.draw(border, 4, sf::LineStrip);

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
