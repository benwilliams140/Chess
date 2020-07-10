#include "Rook.h"

Rook::Rook(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_rook.png" : "./assets/black_rook.png", _size, _col, _row, _colour)
{

}

Rook::~Rook()
{

}

std::vector<sf::Vector2i> Rook::getPossibleMoves(int _rows, int _cols, Piece* [][8])
{
	std::vector<sf::Vector2i> _moves;

	for (int _col = 0; _col < _cols; ++_col)
	{
		if (_col != col) _moves.push_back(sf::Vector2i(_col, row));
	}

	for (int _row = 0; _row < _rows; ++_row)
	{
		if (_row != row) _moves.push_back(sf::Vector2i(col, _row));
	}

	return _moves;
}