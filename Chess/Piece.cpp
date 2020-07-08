#include "Piece.h"

Piece::Piece(std::string _file, int _size, int _col, int _row) : move(0), selected(false)
{
	if (!tex.loadFromFile(_file))
		std::cout << "Error loading file: " << _file << std::endl;

	rect.setSize(sf::Vector2f(_size, _size));
	rect.setOrigin(sf::Vector2f(_size / 2, _size / 2));
	rect.setPosition(sf::Vector2f(_col * _size + _size / 2, _row * _size + _size / 2));
	rect.setTexture(&tex);
	rect.setOutlineColor(sf::Color::Green);
}

Piece::~Piece()
{

}

void Piece::render(Window* _window)
{
	_window->render(rect);
}

void Piece::mouseClicked()
{
	selected = true;
	rect.setScale(sf::Vector2f(.96, .96));
	rect.setOutlineThickness(3);
}

void Piece::reset()
{
	selected = false;
	rect.setScale(sf::Vector2f(1, 1));
	rect.setOutlineThickness(0);
}