#include "Board.h"

Board::Board()
{
	init();
}

Board::~Board()
{

}

void Board::init()
{
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			board[_col][_row] = NULL;
		}
	}

	for (int _col = 0; _col < COLS; ++_col)
	{
		board[_col][1] = new Pawn(TILE_SIZE, _col, 1, 'b');
		board[_col][6] = new Pawn(TILE_SIZE, _col, 6, 'w');
	}

	board[0][0] = new Rook(TILE_SIZE, 0, 0, 'b');
	board[7][0] = new Rook(TILE_SIZE, 7, 0, 'b');
	board[0][7] = new Rook(TILE_SIZE, 0, 7, 'w');
	board[7][7] = new Rook(TILE_SIZE, 7, 7, 'w');

	board[1][0] = new Knight(TILE_SIZE, 1, 0, 'b');
	board[6][0] = new Knight(TILE_SIZE, 6, 0, 'b');
	board[1][7] = new Knight(TILE_SIZE, 1, 7, 'w');
	board[6][7] = new Knight(TILE_SIZE, 6, 7, 'w');

	board[2][0] = new Bishop(TILE_SIZE, 2, 0, 'b');
	board[5][0] = new Bishop(TILE_SIZE, 5, 0, 'b');
	board[2][7] = new Bishop(TILE_SIZE, 2, 7, 'w');
	board[5][7] = new Bishop(TILE_SIZE, 5, 7, 'w');

	board[3][0] = new Queen(TILE_SIZE, 3, 0, 'b');
	board[3][7] = new Queen(TILE_SIZE, 3, 7, 'w');

	board[4][0] = new King(TILE_SIZE, 4, 0, 'b');
	board[4][7] = new King(TILE_SIZE, 4, 7, 'w');
}

void Board::update()
{
	
}

void Board::render(Window* _window)
{
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			sf::RectangleShape _rect;
			_rect.setOrigin(0, 0);
			_rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			_rect.setPosition(sf::Vector2f(_col * TILE_SIZE, _row * TILE_SIZE));
			
			if ((_row + _col) % 2 == 0) _rect.setFillColor(sf::Color::White);
			else _rect.setFillColor(sf::Color(192, 192, 192));

			_window->render(_rect);

			if (board[_col][_row]) board[_col][_row]->render(_window);
		}
	}
}

void Board::mouseClicked(sf::Vector2i _position)
{
	resetBoard();

	int _row = (int)floor(_position.y / TILE_SIZE);
	int _col = (int)floor(_position.x / TILE_SIZE);

	//std::cout << _col << ", " << _row << std::endl;

	if(board[_col][_row]) board[_col][_row]->mouseClicked();
}

void Board::resetBoard()
{
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if(board[_col][_row]) board[_col][_row]->reset();
		}
	}
}

int Board::getCols()
{
	return COLS;
}

int Board::getRows()
{
	return ROWS;
}

int Board::getTileSize()
{
	return TILE_SIZE;
}