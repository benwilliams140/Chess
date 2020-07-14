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
	board.clear();

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
			if (board[_col][_row])
			{
				//std::cout << "Rendering piece at: " << board[_col][_row]->getCol() << ", " << board[_col][_row]->getRow() << "(" << _col << ", " << _row << ")" << std::endl;
				board[_col][_row]->render(_window);
			}
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
			possibleMoves = selectedPiece->getPossibleMoves(board);
			//filterPossibleMoves(_col, _row);
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
			if (board[_col][_row] && board[_col][_row]->getPiece() == 'K')
			{
				init();
				break;
			}

			if (board[_col][_row] && board[_col][_row]->getColour() == selectedPiece->getColour())
			{
				Piece* _piece = board[_col][_row];
				board[selectedPiece->getCol()][selectedPiece->getRow()] = _piece;
				_piece->moveTo(selectedPiece->getCol(), selectedPiece->getRow());
			}
			else
				board[selectedPiece->getCol()][selectedPiece->getRow()] = NULL;

			//delete board[_col][_row];

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
	int _lowerDiagonalLeftRowBound = -1, _lowerDiagonalRightRowBound = -1;
	int _upperDiagonalLeftRowBound = -1, _upperDiagonalRightRowBound = -1;
	int _lowerDiagonalUpColBound = -1, _lowerDiagonalDownColBound = -1;
	int _upperDiagonalUpColBound = -1, _upperDiagonalDownColBound = -1;
	
	for (int _multiple = 1; _multiple < 8; ++_multiple)
	{
		for (int _dCol = -1; _dCol <= 1; ++_dCol)
		{
			for (int _dRow = -1; _dRow <= 1; ++_dRow)
			{
				int _nextCol = _col + _dCol * _multiple;
				int _nextRow = _row + _dRow * _multiple;

				if (board.inBounds(_nextCol, _nextRow))
				{
					//std::cout << _nextRow << ", " << _nextRow << std::endl << std::endl;

					if (board[_nextCol][_nextRow])
					{
						// column bounds
						if (_nextCol < _col && _nextRow == _row && _lowerColBound == -1) _lowerColBound = _nextCol - 1;
						if (_nextCol > _col&& _nextRow == _row && _upperColBound == -1) _upperColBound = _nextCol + 1;

						// row bounds
						if (_nextCol == _col && _nextRow < _row && _lowerRowBound == -1) _lowerRowBound = _nextRow - 1;
						if (_nextCol == _col && _nextRow > _row && _upperRowBound == -1) _upperRowBound = _nextRow + 1;
						
						// diagonal bounds
						if (_nextCol < _col && _nextRow < _row && _lowerDiagonalUpColBound == -1 && _lowerDiagonalLeftRowBound == -1)
						{
							_lowerDiagonalUpColBound = _nextCol - 1;
							_lowerDiagonalLeftRowBound = _nextRow - 1;
						}
						if (_nextCol < _col && _nextRow > _row&& _lowerDiagonalDownColBound == -1 && _upperDiagonalLeftRowBound == -1)
						{
							_lowerDiagonalDownColBound = _nextCol - 1;
							_upperDiagonalLeftRowBound = _nextRow + 1;
						}
						if (_nextCol > _col && _nextRow < _row && _upperDiagonalUpColBound == -1 && _lowerDiagonalRightRowBound == -1)
						{
							_upperDiagonalUpColBound = _nextCol + 1;
							_lowerDiagonalRightRowBound = _nextRow - 1;
						}
						if (_nextCol > _col&& _nextRow > _row&& _upperDiagonalDownColBound == -1 && _upperDiagonalRightRowBound == -1)
						{
							_upperDiagonalDownColBound = _nextCol + 1;
							_upperDiagonalRightRowBound = _nextRow + 1;
						}
					}
				}
			}
		}
	}
	
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
				if (_move.x <= _lowerDiagonalUpColBound && _move.y <= _lowerDiagonalLeftRowBound && _lowerDiagonalUpColBound != -1 && _lowerDiagonalLeftRowBound != -1) return true;
				if (_move.x <= _lowerDiagonalDownColBound && _move.y >= _upperDiagonalLeftRowBound && _lowerDiagonalDownColBound != -1 && _upperDiagonalLeftRowBound != -1) return true;
				if (_move.x >= _upperDiagonalUpColBound && _move.y <= _lowerDiagonalRightRowBound && _upperDiagonalUpColBound != -1 && _lowerDiagonalRightRowBound != -1) return true;
				if (_move.x >= _upperDiagonalDownColBound && _move.y >= _upperDiagonalRightRowBound && _upperDiagonalDownColBound != -1 && _upperDiagonalRightRowBound != -1) return true;

				if (_move.x >= 0 && _move.x < COLS && _move.y >= 0 && _move.y < ROWS)
				{
					if (board[_move.x][_move.y])
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