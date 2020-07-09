#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(int, int, int, char);
	~Rook();

	std::vector<sf::Vector2i> getPossibleMoves(int, int, Piece* [][8]) override;

private:

};

#endif

