#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Window.h"

class Piece
{
public:
	Piece(std::string, int, int, int);
	~Piece();

	void render(Window*);
	void mouseClicked();
	void reset();

private:
	std::string file;
	sf::RectangleShape rect;
	sf::Texture tex;
	
	int move;
	bool selected;
};

#endif