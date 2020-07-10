#include "GUI.h"

GUI::GUI(Window* _window, int _width, int _height) : window(_window), gui(window->getWindow()), width(_width), height(_height)
{
	init();
}

GUI::~GUI()
{
}

void GUI::handleEvent(sf::Event& _event)
{
	//std::cout << _event.type << std::endl;
	gui.handleEvent(_event);
}

void GUI::render()
{
	gui.draw();
	//std::cout << "GUI Drawn." << std::endl;
}

void GUI::init()
{
	panel = tgui::Panel::create({ width, height });
	panel->setPosition(window->getWidth() - width, 0);
	gui.add(panel);

	btnRestart = tgui::Button::create("Restart");
	btnRestart->setPosition(10, 10);
	panel->add(btnRestart, "btnRestart");
}

tgui::Widget::Ptr GUI::getWidgetByName(std::string _name)
{
	std::vector<tgui::Widget::Ptr> _widgets = panel->getWidgets();
	tgui::Widget::Ptr _widget;

	for (auto _it = _widgets.begin(); _it != _widgets.end(); ++_it)
	{
		_widget = *_it;
		
		//std::cout << std::string(_widget->getWidgetName()) << " : " << _name << std::endl;

		if (std::string(_widget->getWidgetName()) == _name) return _widget;
	}

	return NULL;
}