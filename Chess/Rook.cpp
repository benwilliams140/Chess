#include "Rook.h"

Rook::Rook(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_rook.png" : "./assets/black_rook.png", _size, _col, _row)
{

}

Rook::~Rook()
{

}