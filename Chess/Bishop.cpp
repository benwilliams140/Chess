#include "Bishop.h"

Bishop::Bishop(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_bishop.png" : "./assets/black_bishop.png", _size, _col, _row, _colour, 'b')
{

}

Bishop::~Bishop()
{

}

std::vector<sf::Vector2i> Bishop::getPossibleMoves(int _rows, int _cols)
{
	std::vector<sf::Vector2i> _moves;
	return _moves;
}