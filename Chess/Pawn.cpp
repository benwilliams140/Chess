#include "Pawn.h"

Pawn::Pawn(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_pawn.png" : "./assets/black_pawn.png", _size, _col, _row, _colour)
{
	dir = _colour == 'w' ? UP : DOWN;
}

Pawn::~Pawn()
{

}

std::vector<sf::Vector2i> Pawn::getPossibleMoves(int _rows, int _cols)
{
	std::vector<sf::Vector2i> _moves;
	_moves.push_back(sf::Vector2i(col, row + dir));

	if (move == 0) _moves.push_back(sf::Vector2i(col, row + 2 * dir));

	return _moves;
}