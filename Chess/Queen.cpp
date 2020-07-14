#include "Queen.h"

Queen::Queen(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_queen.png" : "./assets/black_queen.png", _size, _col, _row, _colour, 'Q')
{

}

Queen::~Queen()
{

}

std::vector<sf::Vector2i> Queen::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	for (int _col = 0; _col < _board.getCols(); ++_col)
	{
		if (_col != col) _moves.push_back(sf::Vector2i(_col, row));
	}

	for (int _row = 0; _row < _board.getRows(); ++_row)
	{
		if (_row != row) _moves.push_back(sf::Vector2i(col, _row));
	}

	for (int _dCol = -col; _dCol < _board.getCols() - col; ++_dCol)
	{
		int _nextCol = col + _dCol;
		int _rowAbove = row + _dCol;
		int _rowBelow = row - _dCol;

		if (_board.inBounds(_nextCol, _rowAbove)) _moves.push_back(sf::Vector2i(_nextCol, _rowAbove));
		if (_board.inBounds(_nextCol, _rowBelow)) _moves.push_back(sf::Vector2i(_nextCol, _rowBelow));
	}

	return _moves;
}