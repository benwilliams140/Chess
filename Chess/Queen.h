#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(int, int, int, char);
	~Queen();

	std::vector<sf::Vector2i> getPossibleMoves(int, int) override;

private:

};

#endif

