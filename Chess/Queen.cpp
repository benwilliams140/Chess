#include "Queen.h"

Queen::Queen(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_queen.png" : "./assets/black_queen.png", _size, _col, _row)
{

}

Queen::~Queen()
{

}