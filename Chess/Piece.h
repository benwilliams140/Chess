#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Window.h"

class Piece
{
public:
	Piece(std::string, int, int, int, char);
	~Piece();

	void render(Window*);
	void mouseClicked();
	void reset();
	void moveTo(int, int);

	virtual std::vector<sf::Vector2i> getPossibleMoves(int, int, Piece*[][8]);

	int getRow();
	int getCol();
	char getColour();

protected:
	int row, col, size;
	int move;

private:
	char colour;
	std::string file;
	sf::RectangleShape rect;
	sf::Texture tex;

	bool selected;
};

#endif