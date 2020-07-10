#include "Knight.h"

Knight::Knight(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_knight.png" : "./assets/black_knight.png", _size, _col, _row, _colour)
{

}

Knight::~Knight()
{

}

std::vector<sf::Vector2i> Knight::getPossibleMoves(int _rows, int _cols)
{
	std::vector<sf::Vector2i> _moves;
	int _dCol = -2;
	int _dRow = -1;

	for (int _i = 0; _i < 4; ++_i)
	{
		if (col + _dCol >= 0 && col + _dCol < _cols && row + _dRow >= 0 && row + _dRow < _rows)
		{
			_moves.push_back(sf::Vector2i(col + _dCol, row + _dRow));
		}

		if (col + _dRow >= 0 && col + _dRow < _cols && row + _dCol >= 0 && row + _dCol < _rows)
		{
			_moves.push_back(sf::Vector2i(col + _dRow, row + _dCol));
		}

		int _temp = _dCol;
		_dCol = _dRow;
		_dRow = -_temp;
	}

	return _moves;
}