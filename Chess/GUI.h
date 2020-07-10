#ifndef GUI_H
#define GUI_H

#include <TGUI/TGUI.hpp>

#include "Window.h"

class GUI
{
public:
	GUI(Window*);
	~GUI();

	void handleEvent(sf::Event&);
	void render();

private:
	void init();

	tgui::Gui gui;
	tgui::Button btnRestart;
};

#endif