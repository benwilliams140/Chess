#ifndef PIECE_H
#define PIECE_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Window.h"
#include "Array2D.h"

class Piece
{
public:
	Piece(std::string, int, int, int, char, char);
	~Piece();

	void render(Window*);
	void mouseClicked();
	void reset();
	void moveTo(int, int);

	virtual std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&);

	int getRow();
	int getCol();
	char getColour();
	char getPiece();
	int getMove();

protected:
	int row, col, size;
	int move;

private:
	char colour;
	char piece;

	std::string file;
	sf::RectangleShape rect;
	sf::Texture tex;

	bool selected;
};

#endif