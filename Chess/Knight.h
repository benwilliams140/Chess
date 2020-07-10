#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(int, int, int, char);
	~Knight();

	std::vector<sf::Vector2i> getPossibleMoves(int, int) override;

private:

};

#endif