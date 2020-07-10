#include "GUI.h"

GUI::GUI(Window* _window) : gui(_window->getWindow())
{
	init();
}

GUI::~GUI()
{
}

void GUI::handleEvent(sf::Event& _event)
{

}

void GUI::render()
{
	gui.draw();
}

void GUI::init()
{

}