#include "King.h"

King::King(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_king.png" : "./assets/black_king.png", _size, _col, _row)
{

}

King::~King()
{

}