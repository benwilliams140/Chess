#include "Board.h"

Board::Board() : selectedPiece(NULL), takeTurns(true)
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
		if (!takeTurns || board[_col][_row]->getColour() == curPlayer)
		{
			selectedPiece = board[_col][_row];
			selectedPiece->mouseClicked();
			possibleMoves = selectedPiece->getPossibleMoves(ROWS, COLS);
			filterPossibleMoves(_col, _row);
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

void Board::filterPossibleMoves(int _col, int _row)
{
	int _multipleBound = _col > _row ? _col : _row;
	int _lowerRowBound = -1, _upperRowBound = -1;
	int _lowerColBound = -1, _upperColBound = -1;
	int _lowerColLowerRowBound = -1, _upperColUpperRowBound = -1;
	int _lowerColUpperRowBound = -1, _upperColLowerRowBound = -1;

	

	
	for (int _multiple = 1; _multiple < 8; ++_multiple)
	{
		for (int _dCol = -1; _dCol <= 1; ++_dCol)
		{
			for (int _dRow = -1; _dRow <= 1; ++_dRow)
			{
				int _nextCol = _col + _dCol * _multiple;
				int _nextRow = _row + _dRow * _multiple;

				if (_nextCol >= 0 && _nextCol < COLS && _nextRow >= 0 && _nextRow < ROWS)
				{
					//std::cout << _nextRow << ", " << _nextRow << std::endl << std::endl;

					if (board[_nextCol][_nextRow])
					{
						// column bounds
						if (_nextCol < _col && _nextRow == _row && _lowerColBound == -1) _lowerColBound = _nextCol - 1;
						if (_nextCol > _col&& _nextRow == _row && _upperColBound == -1) _upperColBound = _nextCol + 1;

						// row bounds
						if (_nextCol == _col && _nextRow < _row && _lowerRowBound == -1) _lowerRowBound = _nextRow - 1;
						if (_nextCol == _col && _nextRow > _row&& _upperRowBound == -1) _upperRowBound = _nextRow + 1;
						
						/*if (_nextCol < _col && _nextRow < _row && _lowerColLowerRowBound == -1) _lowerColLowerRowBound = _nextCol;
						if (_nextCol < _col && _nextRow > _row && _lowerColUpperRowBound == -1) _lowerColUpperRowBound = _nextCol;
						if (_nextCol > _col&& _nextRow < _row && _upperColLowerRowBound == -1) _upperColLowerRowBound = _nextCol;
						if (_nextCol > _col&& _nextRow > _row && _upperColUpperRowBound == -1) _upperColUpperRowBound = _nextCol;
						if (_nextCol < _col && _nextRow == _row && _lowerColBound == -1) _lowerColBound = _nextCol;
						if (_nextCol > _col&& _nextRow == _row && _upperColBound == -1) _upperColBound = _nextCol;
						if (_nextCol == _col && _nextRow < _row && _lowerRowBound == -1) _lowerRowBound = _nextRow;
						if (_nextCol == _col && _nextRow > _row && _upperRowBound == -1) _upperRowBound = _nextRow;*/
					}
				}
			}
		}
	}

	/*
	std::cout << "Lower Col Bound: " << _lowerColBound << std::endl;
	std::cout << "Upper Col Bound: " << _upperColBound << std::endl;
	std::cout << "Lower Row Bound: " << _lowerRowBound << std::endl;
	std::cout << "Upper Row Bound: " << _upperRowBound << std::endl;
	std::cout << "Lower Col Lower Row Bound: " << _lowerColLowerRowBound << std::endl;
	std::cout << "Lower Col Upper Row Bound: " << _lowerColUpperRowBound << std::endl;
	std::cout << "Upper Col Lower Row Bound: " << _upperColLowerRowBound << std::endl;
	std::cout << "Upper Col Upper Row Bound: " << _upperColUpperRowBound << std::endl;
	*/
	
	possibleMoves.erase(
		std::remove_if(
			possibleMoves.begin(),
			possibleMoves.end(),
			[&](sf::Vector2i _move) -> bool
			{
				if (_move.x <= _lowerColBound && _move.y == _row && _lowerColBound != -1) return true;
				if (_move.x >= _upperColBound && _move.y == _row && _upperColBound != -1) return true;
				if (_move.x == _col && _move.y <= _lowerRowBound && _lowerRowBound != -1) return true;
				if (_move.x == _col && _move.y >= _upperRowBound && _upperRowBound != -1) return true;

				/*if (_move.x < _lowerColLowerRowBound && _move.y < _lowerColLowerRowBound) return true;
				if (_move.x < _lowerColUpperRowBound && _move.y > _lowerColUpperRowBound) return true;
				if (_move.x > _upperColLowerRowBound && _move.y < _upperColLowerRowBound) return true;
				if (_move.x > _upperColUpperRowBound && _move.y > _upperColUpperRowBound) return true;
				if (_move.x < _lowerColBound && _move.y == _row) return true;
				if (_move.x > _upperColBound && _move.y == _row) return true;
				if (_move.x == _col && _move.y < _lowerRowBound) return true;
				if (_move.x == _col && _move.y > _upperRowBound) return true;*/
				
				if (board[_move.x][_move.y])
				{
					if (board[_move.x][_move.y]->getColour() == selectedPiece->getColour()) return true;
				}

				return false;
			}
		),
		possibleMoves.end()
	);
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

void Board::switchTakeTurns()
{
	takeTurns = !takeTurns;
}