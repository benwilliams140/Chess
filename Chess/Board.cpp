#include "Board.h"

Board::Board() : selectedPiece(NULL)
{
	init();
}

Board::~Board()
{

}

void Board::init()
{
	// initializes board to NULL
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if (board[_col][_row]) delete board[_col][_row];
			board[_col][_row] = NULL;
		}
	}

	// initializes black/white pawns
	for (int _col = 0; _col < COLS; ++_col)
	{
		board[_col][1] = new Pawn(TILE_SIZE, _col, 1, 'b');
		board[_col][6] = new Pawn(TILE_SIZE, _col, 6, 'w');
	}

	// initializes black/white rooks
	board[0][0] = new Rook(TILE_SIZE, 0, 0, 'b');
	board[7][0] = new Rook(TILE_SIZE, 7, 0, 'b');
	board[0][7] = new Rook(TILE_SIZE, 0, 7, 'w');
	board[7][7] = new Rook(TILE_SIZE, 7, 7, 'w');

	// initializes black/white knights
	board[1][0] = new Knight(TILE_SIZE, 1, 0, 'b');
	board[6][0] = new Knight(TILE_SIZE, 6, 0, 'b');
	board[1][7] = new Knight(TILE_SIZE, 1, 7, 'w');
	board[6][7] = new Knight(TILE_SIZE, 6, 7, 'w');

	// initializes black/white bishops
	board[2][0] = new Bishop(TILE_SIZE, 2, 0, 'b');
	board[5][0] = new Bishop(TILE_SIZE, 5, 0, 'b');
	board[2][7] = new Bishop(TILE_SIZE, 2, 7, 'w');
	board[5][7] = new Bishop(TILE_SIZE, 5, 7, 'w');

	// initializes black/white queen
	board[3][0] = new Queen(TILE_SIZE, 3, 0, 'b');
	board[3][7] = new Queen(TILE_SIZE, 3, 7, 'w');

	// initializes black/white king
	board[4][0] = new King(TILE_SIZE, 4, 0, 'b');
	board[4][7] = new King(TILE_SIZE, 4, 7, 'w');

	curPlayer = PLAYER_ONE;
}

void Board::update()
{
	
}

void Board::render(Window* _window)
{
	// renders the checkered board
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			sf::RectangleShape _rect;
			_rect.setOrigin(0, 0);
			_rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			_rect.setPosition(sf::Vector2f(_col * TILE_SIZE, _row * TILE_SIZE));
			
			// decides if a square should be white or gray
			if ((_row + _col) % 2 == 0) _rect.setFillColor(sf::Color::White);
			else _rect.setFillColor(sf::Color(192, 192, 192));

			_window->render(_rect);
		}
	}

	// renders the possible moves (if any)
	for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
	{
		sf::Vector2i _move = *_it;
		sf::RectangleShape _rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		
		_rect.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		_rect.setPosition(sf::Vector2f(_move.x * TILE_SIZE + TILE_SIZE / 2, _move.y * TILE_SIZE + TILE_SIZE / 2));
		_rect.setScale(sf::Vector2f(0.96, 0.96));
		_rect.setOutlineColor(sf::Color::Yellow);
		_rect.setOutlineThickness(3);

		if ((_move.x + _move.y) % 2 == 0) _rect.setFillColor(sf::Color::White);
		else _rect.setFillColor(sf::Color(192, 192, 192));

		_window->render(_rect);
	}

	// renders the pieces
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if (board[_col][_row]) board[_col][_row]->render(_window);
		}
	}
}

void Board::mouseClicked(sf::Vector2i _position)
{
	resetBoard();

	int _row = (int)floor(_position.y / TILE_SIZE);
	int _col = (int)floor(_position.x / TILE_SIZE);

	if (_col >= COLS) return;

	//std::cout << _col << ", " << _row << std::endl;

	//selectedPiece = board[_col][_row];

	if (board[_col][_row] && possibleMoves.size() == 0)
	{
		if (board[_col][_row]->getColour() == curPlayer)
		{
			selectedPiece = board[_col][_row];
			selectedPiece->mouseClicked();
			possibleMoves = selectedPiece->getPossibleMoves(ROWS, COLS);
		}
	}
	else checkPossibleMoves(_col, _row);
}

void Board::checkPossibleMoves(int _col, int _row)
{
	for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
	{
		sf::Vector2i _move = *_it;
		if (_move.x == _col && _move.y == _row)
		{
			if (board[_move.x][_move.y])
			{
				if (board[_move.x][_move.y]->getColour() == selectedPiece->getColour()) break;
				else
				{
					char _piece = board[_col][_row]->getPiece();
					
					if (_piece == 'K')
					{
						init();
						break;
					}

					delete board[_col][_row];
				}
			}

			board[selectedPiece->getCol()][selectedPiece->getRow()] = NULL;
			selectedPiece->moveTo(_col, _row);
			board[_col][_row] = selectedPiece;

			curPlayer = curPlayer == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;

			break;
		}
	}

	selectedPiece = NULL;
	possibleMoves.clear();
}

void Board::resetBoard()
{
	// resets each of the piece's selected values every time the mouse is clicked
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if(board[_col][_row]) board[_col][_row]->reset();
		}
	}
}

int Board::getCols()
{
	return COLS;
}

int Board::getRows()
{
	return ROWS;
}

int Board::getTileSize()
{
	return TILE_SIZE;
}