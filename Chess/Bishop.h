#ifndef BISHOP_H
#define BISHOP_H

#define _USE_MATH_DEFINES

#include "Piece.h"
#include <cmath>

class Bishop : public Piece
{
public:
	Bishop(int, int, int, char);
	~Bishop();

	std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&) override;

private:

};

#endif
