#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Window.h"

class Piece
{
public:
	Piece(std::string, int, int, int, char, char);
	~Piece();

	void render(Window*);
	void mouseClicked();
	void reset();
	void moveTo(int, int);

	virtual std::vector<sf::Vector2i> getPossibleMoves(int, int);

	int getRow();
	int getCol();
	char getColour();
	char getPiece();

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