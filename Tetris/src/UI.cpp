#pragma region include system
#include <string>
#pragma endregion

#pragma region include project
#include "Game.hpp"
#include "Player.hpp"
#include "UI.hpp"
#pragma endregion

// render every frame
void UI::Render(char* _pScreen, int _screenWidth, int _screenHeight)
{
	// if game is not started
	if (!m_pGame->IsGameStarted())
	{
		// show start screen
		_pScreen[_screenWidth * 2 - 10] = 'P';
		_pScreen[_screenWidth * 2 - 9] = 'R';
		_pScreen[_screenWidth * 2 - 8] = 'E';
		_pScreen[_screenWidth * 2 - 7] = 'S';
		_pScreen[_screenWidth * 2 - 6] = 'S';
		_pScreen[_screenWidth * 3 - 10] = 'E';
		_pScreen[_screenWidth * 3 - 9] = 'N';
		_pScreen[_screenWidth * 3 - 8] = 'T';
		_pScreen[_screenWidth * 3 - 7] = 'E';
		_pScreen[_screenWidth * 3 - 6] = 'R';
		_pScreen[_screenWidth * 4 - 10] = 'T';
		_pScreen[_screenWidth * 4 - 9] = 'O';
		_pScreen[_screenWidth * 5 - 10] = 'S';
		_pScreen[_screenWidth * 5 - 9] = 'T';
		_pScreen[_screenWidth * 5 - 8] = 'A';
		_pScreen[_screenWidth * 5 - 7] = 'R';
		_pScreen[_screenWidth * 5 - 6] = 'T';
	}

	// if game is over
	else if (m_pGame->IsGameOver())
	{
		// show game over
		_pScreen[_screenWidth * 2 - 10] = 'G';
		_pScreen[_screenWidth * 2 - 9] = 'A';
		_pScreen[_screenWidth * 2 - 8] = 'M';
		_pScreen[_screenWidth * 2 - 7] = 'E';
		_pScreen[_screenWidth * 2 - 5] = 'O';
		_pScreen[_screenWidth * 2 - 4] = 'V';
		_pScreen[_screenWidth * 2 - 3] = 'E';
		_pScreen[_screenWidth * 2 - 2] = 'R';

		// show score
		ShowScore(4, _pScreen, _screenWidth);

		// show restart text
		_pScreen[_screenWidth * 7 - 10] = 'P';
		_pScreen[_screenWidth * 7 - 9] = 'R';
		_pScreen[_screenWidth * 7 - 8] = 'E';
		_pScreen[_screenWidth * 7 - 7] = 'S';
		_pScreen[_screenWidth * 7 - 6] = 'S';
		_pScreen[_screenWidth * 8 - 10] = 'E';
		_pScreen[_screenWidth * 8 - 9] = 'N';
		_pScreen[_screenWidth * 8 - 8] = 'T';
		_pScreen[_screenWidth * 8 - 7] = 'E';
		_pScreen[_screenWidth * 8 - 6] = 'R';
		_pScreen[_screenWidth * 8 - 4] = 'T';
		_pScreen[_screenWidth * 8 - 3] = 'O';
		_pScreen[_screenWidth * 9 - 10] = 'R';
		_pScreen[_screenWidth * 9 - 9] = 'E';
		_pScreen[_screenWidth * 9 - 8] = 'S';
		_pScreen[_screenWidth * 9 - 7] = 'T';
		_pScreen[_screenWidth * 9 - 6] = 'A';
		_pScreen[_screenWidth * 9 - 5] = 'R';
		_pScreen[_screenWidth * 9 - 4] = 'T';
	}

	// if game is runnning
	else
	{
		// show next text
		_pScreen[_screenWidth * 2 - 10] = 'N';
		_pScreen[_screenWidth * 2 - 9] = 'E';
		_pScreen[_screenWidth * 2 - 8] = 'X';
		_pScreen[_screenWidth * 2 - 7] = 'T';

		// show next tetromino
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				_pScreen[_screenWidth * (y + 4) - (10 - x)] = m_pPlayer->GetNextTetromino()[y * 4 + x];

		// show score
		ShowScore(10, _pScreen, _screenWidth);
	}
}

// show score on screen at line
void UI::ShowScore(int _line, char* _pScreen, int _screenWidth)
{
	// show score text
	_pScreen[_screenWidth * _line - 10] = 'S';
	_pScreen[_screenWidth * _line - 9] = 'C';
	_pScreen[_screenWidth * _line - 8] = 'O';
	_pScreen[_screenWidth * _line - 7] = 'R';
	_pScreen[_screenWidth * _line - 6] = 'E';
	_pScreen[_screenWidth * _line - 5] = ':';

	// show number
	if (m_score > 99999999)
		_pScreen[(_screenWidth * (_line + 1)) - 10] = 48 + m_score / 100000000;
	if (m_score > 9999999)
		_pScreen[(_screenWidth * (_line + 1)) - 9] = 48 + m_score / 10000000 % 10;
	if (m_score > 999999)
		_pScreen[(_screenWidth * (_line + 1)) - 8] = 48 + m_score / 1000000 % 10;
	if (m_score > 99999)
		_pScreen[(_screenWidth * (_line + 1)) - 7] = 48 + m_score / 100000 % 10;
	if (m_score > 9999)
		_pScreen[(_screenWidth * (_line + 1)) - 6] = 48 + m_score / 10000 % 10;
	if (m_score > 999)
		_pScreen[(_screenWidth * (_line + 1)) - 5] = 48 + m_score / 1000 % 10;
	if (m_score > 99)
		_pScreen[(_screenWidth * (_line + 1)) - 4] = 48 + m_score / 100 % 10;
	if (m_score > 9)
		_pScreen[(_screenWidth * (_line + 1)) - 3] = 48 + m_score / 10 % 10;
	_pScreen[(_screenWidth * (_line + 1)) - 2] = 48 + m_score % 10;
}
