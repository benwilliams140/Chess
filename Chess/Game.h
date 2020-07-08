#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Window.h"

const std::string TITLE = "Chess";
const unsigned int FRAMERATE = 60;

class Game
{
public:
	Game();

	void start();
	void stop();
	void cleanup();

private:
	void gameloop();
	void getInput();
	void update(float);
	void render();

	Board* board;
	Window* window;

	bool running;
};

#endif