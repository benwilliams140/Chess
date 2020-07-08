#include "Pawn.h"

Pawn::Pawn(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_pawn.png" : "./assets/black_pawn.png", _size, _col, _row)
{

}

Pawn::~Pawn()
{

}