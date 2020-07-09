#include "King.h"

King::King(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_king.png" : "./assets/black_king.png", _size, _col, _row)
{

}

King::~King()
{

}

std::vector<sf::Vector2i> King::getPossibleMoves(int _rows, int _cols, Piece* [][8])
{
	std::vector<sf::Vector2i> _moves;

	for (int _dCol = -1; _dCol <= 1; ++_dCol)
	{
		for (int _dRow = -1; _dRow <= 1; ++_dRow)
		{
			int _nextCol = col + _dCol;
			int _nextRow = row + _dRow;

			if (_nextCol >= 0 && _nextCol < _cols)
			{
				if (_nextRow >= 0 && _nextRow < _rows)
				{
					if (_nextRow != row || _nextCol != col)
					{
						_moves.push_back(sf::Vector2i(_nextCol, _nextRow));
					}
				}
			}
		}
	}

	return _moves;
}