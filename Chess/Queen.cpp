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

	

	return _moves;
}