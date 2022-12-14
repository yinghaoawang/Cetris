#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

namespace Cetris {
	class Tetromino;

	class Board {
	public:
		static const int WIDTH = 10;
		static const int HEIGHT = 20;
		sf::Vector2f position{ 50., 20.};

		void render(sf::RenderWindow&);
		void tick();
		void manageInput(sf::Event&, sf::RenderWindow&, sf::Time&);

		class Tile {
		public:
			static const int WIDTH = 25;
			static const int HEIGHT = 25;

			Tile(sf::Color&);
			sf::Color color;
		};

		std::vector<std::vector<Tile*>> tiles{ HEIGHT, std::vector<Tile*>(WIDTH, nullptr) };
		Tetromino* tetrominoPtr;

		Board();
		~Board() {
			for (int i = 0; i < tiles.size(); i++) {
				for (int j = 0; j < tiles[i].size(); j++) {
					delete tiles[i][j];
				}
			}
			delete tetrominoPtr;
		}

		bool isTetrominoKickable(Tetromino&, sf::Vector2i*);
		void handleTetrominoCollision();
		bool isTetrominoOutOfBounds(Tetromino&, sf::Vector2i);
		bool isTetrominoColliding(Tetromino&, sf::Vector2i);

		void setIPiece(Tetromino&);
		void setOPiece(Tetromino&);
		void setJPiece(Tetromino&);
		void setLPiece(Tetromino&);
		void setZPiece(Tetromino&);
		void setSPiece(Tetromino&);
		void setTPiece(Tetromino&);


	private:
		void solidifyTetromino();
		void spawnNewTetromino();
		bool anyRowsClearable(std::vector<int>*);
		void clearRows(const std::vector<int>&);

		
	};
}
