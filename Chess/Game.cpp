#include "Game.h"

Game::Game() : running(false)
{
	board = new Board();

	int _width = board->getCols() * board->getTileSize() + GUI_WIDTH;
	int _height = board->getRows() * board->getTileSize();

	window = new Window(TITLE, _width, _height);
	gui = new GUI(window, GUI_WIDTH, _height);
}

void Game::start()
{
	running = true;
	gameloop();
}

void Game::stop()
{
	running = false;
}

void Game::cleanup()
{
	delete board;
}

void Game::gameloop()
{
	sf::Clock _clock;
	window->setFrameLimit(60);

	initGUI();

	while (running)
	{
		getInput();
		update(_clock.restart().asSeconds());
		render();
	}
}

void Game::getInput()
{
	sf::Event _event;

	while (window->pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed) stop();

		if (_event.type == sf::Event::MouseButtonPressed) board->mouseClicked(window->getMousePosition());

		gui->handleEvent(_event);
	}
}

void Game::update(float _deltaTime)
{
	board->update();
}

void Game::render()
{
	window->clear();

	board->render(window);
	gui->render();

	window->display();
}

void Game::initGUI()
{
	tgui::Widget::Ptr _widget;
	
	_widget = gui->getWidgetByName("btnRestart");
	_widget->connect(tgui::Signals::Button::Pressed, [&]()
		{
			//std::cout << "Resetting" << std::endl;
			board->init();
		});
}