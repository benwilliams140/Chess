#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#define PLAYER_ONE	'w'
#define PLAYER_TWO	'b'

const unsigned int COLS = 8;
const unsigned int ROWS = 8;
const unsigned int TILE_SIZE = 100;

class Board
{
public:
	Board();
	~Board();

	void init();
	void update();
	void render(Window*);
	void mouseClicked(sf::Vector2i);
	void resetBoard();

	int getCols();
	int getRows();
	int getTileSize();

	void switchTakeTurns();

private:
	void checkPossibleMoves(int, int);

	Piece* board[COLS][ROWS];
	Piece* selectedPiece;
	std::vector<sf::Vector2i> possibleMoves;

	char curPlayer;
	bool takeTurns;
};

#endif