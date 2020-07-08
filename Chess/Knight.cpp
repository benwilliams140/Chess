#include "Knight.h"

Knight::Knight(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_knight.png" : "./assets/black_knight.png", _size, _col, _row)
{

}

Knight::~Knight()
{

}