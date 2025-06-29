#pragma region include system
#include <windows.h>
#pragma endregion

#pragma region include project
#include "UI.hpp"
#include "Player.hpp"
#include "Playfield.hpp"
#pragma endregion

// constructor
Playfield::Playfield(int _playfieldWidth, int _playfieldHeight)
{
	// set playfield width and height
	m_playfieldWidth = _playfieldWidth;
	m_playfieldHeight = _playfieldHeight;

	// set position of starting field
	m_pos.X = 1;
	m_pos.Y = 1;

	// create playfield string array
	m_pPlayfield = new char[m_playfieldWidth * m_playfieldHeight];

	// reset playfield
	Reset();
}

// destructor
Playfield::~Playfield()
{
	// clear memory
	delete(m_pPlayfield);
}

// update every frame
void Playfield::Update(float _deltaTime)
{
	// line is full decrease time to complete row until 0 or below
	if (m_fullLines && m_timeToCompleteNextRow > 0.0f)
		m_timeToCompleteNextRow -= _deltaTime;

	// if there is one line complete with blocks
	IsLineFull();

	// if at least one line is full and time to complete row is below 0
	if (m_fullLines && m_timeToCompleteNextRow <= 0.0f)
	{
		// remove line(s)
		RemoveLine();

		// move all possible blocks down
		MoveBlocksDown();

		// reset timer for completion next row
		m_timeToCompleteNextRow = WAIT_TIME_COMPLETED_ROW_MS / 1000.0f;
	}

}

// render every frame
void Playfield::Render(char* _pScreen, int _screenWidth, int _screenHeight)
{
	// check playfield array
	for (int y = 0; y < m_playfieldHeight; y++)
		// set screen fields depending on playfield field with position offset
		for (int x = 0; x < m_playfieldWidth; x++)
			if(m_pPlayfield[y * m_playfieldWidth + x] != ' ')
				_pScreen[(static_cast<int>(m_pos.Y) * _screenWidth + static_cast<int>(m_pos.X)) + (y * _screenWidth + x)] = m_pPlayfield[y * m_playfieldWidth + x];
}

// if player is colliding with the playfield
bool Playfield::IsColliding(Player* _pPlayer)
{
	// save current tetromino to avoid copy every time
	const char* _currentTetromino = _pPlayer->GetCurrentTetromino();

	// check player tetromino
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			// if collide return true
			if (_currentTetromino[y * 4 + x] != ' ' &&
				m_pPlayfield[static_cast<int>((_pPlayer->GetPos() - m_pos).Y + y) * m_playfieldWidth + static_cast<int>((_pPlayer->GetPos() - m_pos).X + x)] != ' ')
				return true;
	
	// if no collision return false
	return false;
}

// add players current tetromino to playfield
void Playfield::AddTetrominoToPlayfield(Player* _pPlayer)
{
	// save current tetromino to avoid copy every time
	const char* _currentTetromino = _pPlayer->GetCurrentTetromino();

	// check player tetromino
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			// if current block is displayed by tetromino add block to playfield
			if (_currentTetromino[y * 4 + x] != ' ')
				m_pPlayfield[static_cast<int>((_pPlayer->GetPos() - m_pos).Y + y) * m_playfieldWidth + static_cast<int>((_pPlayer->GetPos() - m_pos).X + x)] = _currentTetromino[y * 4 + x];

	// increase score by 1 and update ui score
	m_playerScore++;
	m_pUI->SetScore(m_playerScore);

	// check player score if speed is increasing
	CheckPlayerScoreToIncreaseSpeed();
}

// reset playfield
void Playfield::Reset()
{
	// check playfield array
	for (int y = 0; y < m_playfieldHeight; y++)
	{
		for (int x = 0; x < m_playfieldWidth; x++)
		{
			// if first or last column or last row draw #
			if ((x == 0 || x == m_playfieldWidth - 1) || y == m_playfieldHeight - 1)
				m_pPlayfield[y * m_playfieldWidth + x] = '#';
			// everything else draw empty field
			else
				m_pPlayfield[y * m_playfieldWidth + x] = ' ';
		}
	}

	// reset player score and update on ui
	m_playerScore = 0;
	if(m_pUI)
		m_pUI->SetScore(m_playerScore);

	// reset score that is needed for increase player speed
	m_playerScoreToIncreaseSpeed = 100.0f;
}

// if any line is complete from bottom to top
void Playfield::IsLineFull()
{
	// check playfield height from bottom top top
	for (int y = m_playfieldHeight - 2; y >= 0; y--)
	{
		// reset blocks count
		m_blockCountPerRow = 0;

		// check playfield width
		for (int x = 1; x < m_playfieldWidth - 1; x++)
		{
			// if block was marked as = from last frame
			if (m_pPlayfield[y * m_playfieldWidth + x] == '=')
				// continue to next line
				continue;

			// if current block is used add block count
			if (m_pPlayfield[y * m_playfieldWidth + x] != ' ')
				m_blockCountPerRow++;
		}

		// if all blocks used
		if (m_blockCountPerRow == m_playfieldWidth - 2)
		{
			// increase full lines
			m_fullLines++;

			// check playfield width
			for (int x = 1; x < m_playfieldWidth - 1; x++)
				// set every block to =
				m_pPlayfield[y * m_playfieldWidth + x] = '=';
		}
	}
}

// remove line from playfield
void Playfield::RemoveLine()
{
	// check playfield height from bottom top top
	for (int y = m_playfieldHeight - 2; y >= 0; y--)
		// check playfield width
		for (int x = 1; x < m_playfieldWidth - 1; x++)
			// if current block is = replace with empty
			if (m_pPlayfield[y * m_playfieldWidth + x] == '=')
				m_pPlayfield[y * m_playfieldWidth + x] = ' ';

	// increase score by 5 multiplied by full lines
	m_playerScore += 5 * m_fullLines * m_fullLines;

	// check player score if speed is increasing
	CheckPlayerScoreToIncreaseSpeed();

	// set score on ui
	m_pUI->SetScore(m_playerScore);

	// reset full lines
	m_fullLines = 0;
}

// check player score to increase speed
void Playfield::CheckPlayerScoreToIncreaseSpeed()
{
	// as long as player score if higher than needed for increase spped
	while (m_playerScore >= m_playerScoreToIncreaseSpeed)
	{
		// increase score that is needed to speed it 50%
		m_playerScoreToIncreaseSpeed *= 1.5;

		// increase player speed
		m_pPlayer->IncreaseSpeed();
	}
}

// move all blocks down that have no blocks below
void Playfield::MoveBlocksDown()
{
	// temp y position to move blocks down
	int tempY = 0;

	// check playfield height from bottom top top
	for (int y = m_playfieldHeight - 2; y >= 0; y--)
	{
		// check playfield width
		for (int x = 1; x < m_playfieldWidth - 1; x++)
		{
			// reset temp y to current row
			tempY = y + 1;

			// if current block is used
			if (m_pPlayfield[y * m_playfieldWidth + x] != ' ')
			{
				// while block can move down
				while (m_pPlayfield[tempY * m_playfieldWidth + x] == ' ')
				{
					// move block down
					m_pPlayfield[tempY * m_playfieldWidth + x] = m_pPlayfield[(tempY - 1) * m_playfieldWidth + x];
					m_pPlayfield[(tempY - 1) * m_playfieldWidth + x] = ' ';
					
					// move temp y one row down
					tempY++;
				}
			}
		}
	}
}
