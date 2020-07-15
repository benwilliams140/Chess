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

	// Even Index : Column | Odd Index : Row
	// 0, 1: Top Left | -1, -1
	// 2, 3: Top Right | 1, -1
	// 4, 5: Bottom Left | -1, 1
	// 6, 7: Bottom Right | 1, 1
	int _bounds[8];
	_bounds[0] = _bounds[1] = _bounds[3] = _bounds[4] = -1;
	_bounds[2] = _bounds[6] = _board.getCols();
	_bounds[5] = _bounds[7] = _board.getRows();

	for (int _delta = 1; _delta < _board.getCols(); ++_delta)
	{
		for (int _rad = 1; _rad <= 4; ++_rad)
		{
			int _colMultiple = (int)cos(_rad * M_PI);
			int _rowMultiple = -(int)cos(floor((_rad - 1) / 2) * M_PI);
			
			//std::cout << _colMultiple << ", " << _rowMultiple << std::endl;
		}
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