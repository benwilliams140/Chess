#include "Pawn.h"

Pawn::Pawn(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_pawn.png" : "./assets/black_pawn.png", _size, _col, _row, _colour, 'p')
{
	dir = _colour == 'w' ? UP : DOWN;
}

Pawn::~Pawn()
{

}

std::vector<sf::Vector2i> Pawn::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	if (row + dir >= 0 && row + dir < _board.getRows())
	{
		if(!_board[col][row + dir]) _moves.push_back(sf::Vector2i(col, row + dir));
		if (col - 1 >= 0)
			if (_board[col - 1][row + dir]) _moves.push_back(sf::Vector2i(col - 1, row + dir));
		if (col + 1 < _board.getCols())
			if (_board[col + 1][row + dir]) _moves.push_back(sf::Vector2i(col + 1, row + dir));
	}

	if (move == 0) _moves.push_back(sf::Vector2i(col, row + 2 * dir));

	return _moves;
}