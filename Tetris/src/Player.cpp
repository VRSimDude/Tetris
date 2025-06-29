#pragma region include system
#include <cstdlib>
#include <windows.h>
#pragma endregion

#pragma region include project
#include "Game.hpp"
#include "Playfield.hpp"
#include "Player.hpp"
#pragma endregion

// constructor
Player::Player(Playfield* _pPlayfield)
{
	// save playfield reference
	m_pPlayfield = _pPlayfield;

	// index to step forward within tetromino array
	int index = 0;

	// tetromino 1
	m_tetrominos[0].append(L"  X ");
	m_tetrominos[0].append(L"  X ");
	m_tetrominos[0].append(L"  X ");
	m_tetrominos[0].append(L"  X ");

	// tetromino 2
	m_tetrominos[1].append(L"  O ");
	m_tetrominos[1].append(L" OO ");
	m_tetrominos[1].append(L" O  ");
	m_tetrominos[1].append(L"    ");

	// tetromino 3
	m_tetrominos[2].append(L" O  ");
	m_tetrominos[2].append(L" OO ");
	m_tetrominos[2].append(L"  O ");
	m_tetrominos[2].append(L"    ");

	// tetromino 4
	m_tetrominos[3].append(L"    ");
	m_tetrominos[3].append(L" $$ ");
	m_tetrominos[3].append(L" $$ ");
	m_tetrominos[3].append(L"    ");

	// tetromino 5
	m_tetrominos[4].append(L"  D ");
	m_tetrominos[4].append(L" DD ");
	m_tetrominos[4].append(L"  D ");
	m_tetrominos[4].append(L"    ");

	// tetromino 6
	m_tetrominos[5].append(L"    ");
	m_tetrominos[5].append(L" MM ");
	m_tetrominos[5].append(L"  M ");
	m_tetrominos[5].append(L"  M ");

	// tetromino 7
	m_tetrominos[6].append(L"    ");
	m_tetrominos[6].append(L" MM ");
	m_tetrominos[6].append(L" M  ");
	m_tetrominos[6].append(L" M  ");

	// create current, next and rotated tetromino space
	m_pCurrentTetromino = new char[16];
	m_pNextTetromino = new char[16];
	m_pTetrominoBeforeRotate = new char[16];

	// reset first time to have a next tetromino
	ResetToTop();

	// reset second time to set current tetromino to next and new next one
	ResetToTop();
}

// destructor
Player::~Player()
{
	delete m_pCurrentTetromino;
	delete m_pNextTetromino;
	delete m_pTetrominoBeforeRotate;
}

// update every frame
void Player::Update(float _deltaTime)
{
	if ((0x8000 & GetAsyncKeyState(VK_ESCAPE)) != 0)
	{
		m_pGame->StopGame();
		return;
	}

	// update input for current frame
	m_isArrowDownThisFrame[0] = (0x8000 & GetAsyncKeyState(VK_UP)) != 0;
	m_isArrowDownThisFrame[1] = (0x8000 & GetAsyncKeyState(VK_LEFT)) != 0;
	m_isArrowDownThisFrame[2] = (0x8000 & GetAsyncKeyState(VK_DOWN)) != 0;
	m_isArrowDownThisFrame[3] = (0x8000 & GetAsyncKeyState(VK_RIGHT)) != 0;
	m_isSpaceDownThisFrame = (0x8000 & GetAsyncKeyState(VK_SPACE)) != 0;
	m_isReturnDownThisFrame = (0x8000 & GetAsyncKeyState(VK_RETURN)) != 0;

	// if game was not started
	if (!m_pGame->IsGameStarted())
		// if return is not pressed return
		if (!m_isReturnDownThisFrame)
			return;
		// if return is pressed start game
		else
			m_pGame->StartGame();

	// if game over
	if (m_pGame->IsGameOver())
	{
		// if return is not pressed reset game
		if (m_isReturnDownThisFrame)
			m_pGame->Reset();

		// return
		return;
	}

	// if space was pressed down this frame
	if (!m_isSpaceDownLastFrame && m_isSpaceDownThisFrame)
		// try to rotate current tetromino
		RotateTetromino();

	// if up arrow key was pressed down this frame move down until collision
	if (!m_isArrowDownLastFrame[0] && m_isArrowDownThisFrame[0])
	{
		// as long as there is no collision move down
		while (!m_pPlayfield->IsColliding(this))
			m_pos.Y++;

		// move player one step back
		m_pos.Y--;

		// add tetromino to playfield
		m_pPlayfield->AddTetrominoToPlayfield(this);

		// set random tetromino and position at top of playfield
		ResetToTop();
	}
	// if not up arrow key was pressed down this frame move normally
	else
	{
		// save player position before movement left right
		m_posBeforeMovement = m_pos;

		// if left arrow key was pressed down this frame add movement left
		if (!m_isArrowDownLastFrame[1] && m_isArrowDownThisFrame[1])
			m_pos.X--;

		// if left arrow key was pressed down this frame add movement left
		if (!m_isArrowDownLastFrame[3] && m_isArrowDownThisFrame[3])
			m_pos.X++;

		// if player collides with playfield reset movement
		if (m_pPlayfield->IsColliding(this))
			m_pos = m_posBeforeMovement;

		// save player position before movement auto down
		m_posBeforeMovement = m_pos;

		// try to move player
		m_pos.Y += m_movementSpeedDown * _deltaTime;

		// if down arrow key was pressed down this frame add movement down
		if (!m_isArrowDownLastFrame[2] && m_isArrowDownThisFrame[2])
			m_pos.Y++;

		// if player collides with playfield
		if (m_pPlayfield->IsColliding(this))
		{
			// reset movement
			m_pos = m_posBeforeMovement;

			// add tetromino to playfield
			m_pPlayfield->AddTetrominoToPlayfield(this);

			// set random tetromino and position at top of playfield
			ResetToTop();
		}
	}

	// update input for last frame
	m_isArrowDownLastFrame[0] = m_isArrowDownThisFrame[0];
	m_isArrowDownLastFrame[1] = m_isArrowDownThisFrame[1];
	m_isArrowDownLastFrame[2] = m_isArrowDownThisFrame[2];
	m_isArrowDownLastFrame[3] = m_isArrowDownThisFrame[3];
	m_isSpaceDownLastFrame = m_isSpaceDownThisFrame;
	m_isReturnDownLastFrame = m_isReturnDownThisFrame;
}

// render every frame
void Player::Render(char* _pScreen, int _screenWidth, int _screenHeight)
{
	// check player current tetromino
	for (int y = 0; y < 4; y++)
		// set screen fields depending on current tetromino with player position
		for (int x = 0; x < 4; x++)
			if(m_pCurrentTetromino[y * 4 + x] != ' ')
				_pScreen[static_cast<int>(m_pos.Y) * _screenWidth + static_cast<int>(m_pos.X) + (y * _screenWidth + x)] = m_pCurrentTetromino[y * 4 + x];
}

// reset player
void Player::Reset()
{
	// reset movement speed and to the top
	m_movementSpeedDown = 2.5f;
	ResetToTop();
}

// increase speed
void Player::IncreaseSpeed()
{
	// increase movement speed by 10%
	m_movementSpeedDown *= 1.1f;
}

// rotate tetromino counter clock wise
void Player::RotateTetromino()
{
	// save current tetromino
	for (int i = 0; i < 16; i++)
		m_pTetrominoBeforeRotate[i] = m_pCurrentTetromino[i];

	// rotate current tetromino
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4;x++)
			m_pCurrentTetromino[y * 4 + x] = m_pTetrominoBeforeRotate[3 + (x * 4) - y];

	// if rotated tetromino collide with playfield
	if (m_pPlayfield->IsColliding(this))
		// reset current tetromino
		for (int i = 0; i < 16; i++)
			m_pCurrentTetromino[i] = m_pTetrominoBeforeRotate[i];
}

// reset player to top of playfield with new random tetromino and position
void Player::ResetToTop()
{
	// copy next tetromino to current tetromino
	for (int i = 0; i < 16; i++)
		m_pCurrentTetromino[i] = m_pNextTetromino[i];

	// get random number for next tetromino
	int random = rand() % 7;

	// set next tetromino depending on random
	for (int i = 0; i < 16; i++)
		m_pNextTetromino[i] = m_tetrominos[random][i];

	// set player start position
	random = rand() % (m_pPlayfield->GetPlayfieldWidth() - 3);

	// set player start position
	m_pos.Y = m_pPlayfield->GetPos().Y;
	m_pos.X = m_pPlayfield->GetPos().X + random;

	// if player collides with playfield at spawn set game over
	if (m_pPlayfield->IsColliding(this))
		m_pGame->GameOver();
}
