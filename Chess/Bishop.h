#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(int, int, int, char);
	~Bishop();

	std::vector<sf::Vector2i> getPossibleMoves(int, int) override;

private:

};

#endif
