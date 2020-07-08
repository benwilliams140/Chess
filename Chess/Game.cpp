#include "Game.h"

Game::Game() : running(false)
{
	board = new Board();

	int _width = board->getCols() * board->getTileSize();
	int _height = board->getRows() * board->getTileSize();

	window = new Window(TITLE, _width, _height);
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

	window->display();
}