#include "Bishop.h"

Bishop::Bishop(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_bishop.png" : "./assets/black_bishop.png", _size, _col, _row, _colour, 'b')
{

}

Bishop::~Bishop()
{

}

std::vector<sf::Vector2i> Bishop::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	int topLeftBound, topRightBound, bottomLeftBound, bottomRightBound;
	topLeftBound = topRightBound = bottomLeftBound = bottomRightBound = -1;

	for (int _dCol = -col; _dCol < _board.getCols() - col; ++_dCol)
	{
		int _nextCol = col + _dCol;
		int _rowAbove = row + _dCol;
		int _rowBelow = row - _dCol;

		if (_rowAbove >= 0 && _rowAbove < _board.getRows()) _moves.push_back(sf::Vector2i(_nextCol, _rowAbove));
		if (_rowBelow >= 0 && _rowBelow < _board.getRows()) _moves.push_back(sf::Vector2i(_nextCol, _rowBelow));
	}

	return _moves;
}