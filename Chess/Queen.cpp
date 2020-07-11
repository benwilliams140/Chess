#include "Queen.h"

Queen::Queen(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_queen.png" : "./assets/black_queen.png", _size, _col, _row, _colour, 'Q')
{

}

Queen::~Queen()
{

}

std::vector<sf::Vector2i> Queen::getPossibleMoves(int _rows, int _cols)
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

	for (int _dCol = -col; _dCol < _cols - col; ++_dCol)
	{
		int _nextCol = col + _dCol;
		int _rowAbove = row + _dCol;
		int _rowBelow = row - _dCol;

		if (_rowAbove >= 0 && _rowAbove < _rows) _moves.push_back(sf::Vector2i(_nextCol, _rowAbove));
		if (_rowBelow >= 0 && _rowBelow < _rows) _moves.push_back(sf::Vector2i(_nextCol, _rowBelow));
	}

	return _moves;
}